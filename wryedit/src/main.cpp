#include "wry/global.h"
#include "wry/gfx.h"
#include "wry/io.h"

#include "wry/res/system.h"

#include <fstream>
#include <thread>
#include <chrono>



class Entity : public wry::io::ISerializable {
public:
	Entity() {}
	
	template <typename Archive>
	Entity(Archive& context) : wry::io::ISerializable(context) {
		context.read("simple", &_simple);
	}

	template <typename Archive>
	bool_t serialize(Archive& context) {
		context.write("simple", _simple);
		return true;
	}

	std::string simple() const { return _simple; }

private:
	std::string _simple;
};

template <typename TResult>
TResult func(std::function<TResult()> f) {
    return TResult();
}

template <typename Fun>
auto func(Fun f) -> decltype(f()) {
    return func(std::function<decltype(f())>(f));
}

int main(int argv, char** args) {

	wry::res::System system;
	wry::res::TypeResolver resolver;

	std::function<Entity*(wry::io::JsonSerializationReader&)> lambda = [](wry::io::JsonSerializationReader& var) -> Entity* {
		return new Entity(var);
	};

 	resolver.add<Entity*, wry::io::JsonSerializationReader&>("Entity", lambda);
	
	system.mount("./bin/data.json", resolver);
	auto entity = system.find<Entity>("entity");

	while(true) {
		Entity* test = (Entity*)entity.get();
		std::this_thread::sleep_for (std::chrono::seconds(5));
	}

	return 0;
}

/* 
resources
class TypeResolver {
public:
	template <typename Archive>
	vptr_t create(gsl::czstring name, Archive& context) {
		return new Entity(context);
	}

	void free(vptr_t ptr) {
		delete ptr;
	}
};

enum ResourceEvent {
	changed
};

class Resource {
public:

	Resource() {
		_this = nullptr;
	}

	template <typename Archive>
	Resource(Archive& context) {
		_this = nullptr;
		load(context);
	}

	template <typename Archive>
	void load(Archive& context) {
		if(_this) this->destroy();

_type = "";
		//context.read("name", &_name);
		//context.read("type", &_type);

		TypeResolver type;
		_this = type.create(_type.c_str(), context);
	}

	void destroy() {
		TypeResolver type;
		type.free(_this);
		_this = nullptr;
	}

	vptr_t get() {
		return _this;
	}

private:
	std::string _name;
	std::string _type;

	vptr_t _this;
};

template<typename T>
class ResourceReference {
public:
	ResourceReference(Resource& res) : _res(res) {
		
	}

	ResourceReference<T> operator =(const ResourceReference<T> & parent) {
		return ResourceReference<T>(parent._res);
	}

	T* get() { return (T*)_res.get(); }
	Resource& _res;

};


class Entity : public wry::io::ISerializable {
public:
	Entity() {}

	void update() {
		
	}
	
	template <typename Archive>
	Entity(Archive& context) : wry::io::ISerializable(context) {
		context.read("simple", &_simple);
		//context.read("complex", &_complex);
		//context.read("simpleVector", &_simpleVector);
		//context.read("complexVector", &_complexVector);
		//context.read("simpleMap", &simpleMap);
		//context.read("complexMap", &complexMap);
	}

	template <typename Archive>
	bool_t serialize(Archive& context) {
		context.write("simple", _simple);
		//context.write("complex", _complex);
		//context.write("simpleVector", _simpleVector);
		//context.write("complexVector", _complexVector);
		return true;
	}

	std::string simple() const { return _simple; }
	//SampleInnerGO& complex() { return _complex; }

private:
	std::string _simple;
	//SampleInnerGO _complex;
	//std::vector<uint_t> _simpleVector;
	//std::vector<SampleInnerGO> _complexVector;

	//std::map<gsl::czstring, uint_t> simpleMap;
	//std::map<gsl::czstring, ISerializable> complexMap;
};

typedef ResourceReference<Entity> EntityRef;

class Scene {
public:
	template<typename Archive>
	Scene(Archive& archive) {

	}

	void update() {
		for(auto& entity : _entities) {
			entity.get()->update();
		}
	}

private:
	Resource* _resource;
	std::vector<EntityRef> _entities;
	
};



class Repository {
public:

	template <typename Archive>
	void on_change(Archive& context, Resource& resource) {
		resource.load(context);
	}

private:
};

class System {
public:
	System() {
		load();
		_thread = std::thread([&]()-> void {    
			wry::io::FileWatcher fw{"./", std::chrono::milliseconds(5000)};

			fw.start([&] (std::string path_to_watch, wry::io::FileStatus status) -> void {
				if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != wry::io::FileStatus::erased) {
					return;
				}

				switch(status) {
					case wry::io::FileStatus::created:
						std::cout << "File created: " << path_to_watch << '\n';
						break;
					case wry::io::FileStatus::modified:
						load();
						std::cout << "File modified: " << path_to_watch << '\n';
						break;
					case wry::io::FileStatus::erased:
						std::cout << "File erased: " << path_to_watch << '\n';
						break;
					default:
						std::cout << "Error! Unknown file status.\n";
				}
			});
		});
	}

	void load() {
		std::string filepath = "./bin/data.json";

		std::ifstream i(filepath);
		if(!i) throw;
		json j;
		i >> j;
		_resource.load(wry::io::JsonSerializationReader(j));
	}

	template<typename T>
	ResourceReference<T> get(gsl::czstring path) {
		return ResourceReference<T>( _resource );
	}

private:
	std::thread _thread;
	std::vector<Repository> _repository;
	Resource _resource;
};

class SceneMgr {
	ResourceReference<Entity> _scene;

	void load(gsl::czstring name) {
		System system;
		_scene = system.get<Entity>(name);
	}

	void update() {
		_scene.get()->update();
	}
};



filewatcher
int main(int argv, char** args) {
    // Create a FileWatcher instance that will check the current folder for changes every 5 seconds
    wry::io::FileWatcher fw{"./", std::chrono::milliseconds(5000)};

    // Start monitoring a folder for changes and (in case of changes)
   // run a user provided lambda function
    fw.start([] (std::string path_to_watch, wry::io::FileStatus status) -> void {
        // Process only regular files, all other file types are ignored
        if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != wry::io::FileStatus::erased) {
            return;
        }

        switch(status) {
            case wry::io::FileStatus::created:
                std::cout << "File created: " << path_to_watch << '\n';
                break;
            case wry::io::FileStatus::modified:
                std::cout << "File modified: " << path_to_watch << '\n';
                break;
            case wry::io::FileStatus::erased:
                std::cout << "File erased: " << path_to_watch << '\n';
                break;
            default:
                std::cout << "Error! Unknown file status.\n";
        }
    });

	return 0;
} */

/* serialization

class SampleInnerGO : wry::io::ISerializable {
public:
	SampleInnerGO() {}


	template <typename Archive>
	SampleInnerGO(Archive& context) : wry::io::ISerializable(context) {
		context.read("simple", &_simple);
	}

	template <typename Archive>
	bool_t serialize(Archive& context) {
		context.write("simple", _simple);
		return true;
	}

	uint_t simple() const { return _simple; }

private:
	uint_t _simple;
};

class SampleGO : wry::io::ISerializable {
public:
	SampleGO() {}
	
	template <typename Archive>
	SampleGO(Archive& context) : wry::io::ISerializable(context) {
		context.read("simple", &_simple);
		context.read("complex", &_complex);
		context.read("simpleVector", &_simpleVector);
		context.read("complexVector", &_complexVector);
		//context.read("simpleMap", &simpleMap);
		//context.read("complexMap", &complexMap);
	}

	template <typename Archive>
	bool_t serialize(Archive& context) {
		context.write("simple", _simple);
		context.write("complex", _complex);
		context.write("simpleVector", _simpleVector);
		context.write("complexVector", _complexVector);
		return true;
	}

	std::string simple() const { return _simple; }
	//SampleInnerGO& complex() { return _complex; }

private:
	std::string _simple;
	SampleInnerGO _complex;
	std::vector<uint_t> _simpleVector;
	std::vector<SampleInnerGO> _complexVector;

	//std::map<gsl::czstring, uint_t> simpleMap;
	//std::map<gsl::czstring, ISerializable> complexMap;
};


	auto object = SampleGO(wry::io::JsonSerializationReader(json::parse("{ \"simple\": \"happy\", \"complex\": { \"simple\": 300 }, \"simpleVector\": [1,2,3,4], \"complexVector\": [ { \"simple\": 500 }, { \"simple\": 600 } ] }" )));
	
	json container;
	wry::io::JsonSerializationWriter writer(container);

	object.serialize(writer);

	std::string s = container.dump();

	auto ptr = malloc(65536);
	wry::io::Stream stream(ptr);
	
	wry::io::BinarySerializationWriter bwriter(stream);
	object.serialize(bwriter);
	stream.reset();
	
	auto object2 = SampleGO(wry::io::BinarySerializationReader(stream));

	free(ptr);
	return 0;
}
*/

/*
struct TypeDescriptor {
public:
	uint_t 				id;
	gsl::czstring 		name;
	std::function<ISerializable> ctor();
};

struct ObjectDescriptor {
public:
	uint_t 			id;
	gsl::czstring 	name;
	TypeDescriptor	type;
};

class ITypeResolver {
public:
	//TypeDescriptor& add(gsl::czstring name, std::function<ISerializable> ctor) {}
	TypeDescriptor& lookup(gsl::czstring name) {}
	TypeDescriptor& lookup(uint_t) {}
};
*/


/* init
[{
	engine: {
		name: "engine"
		type: "wry::Engine",
		memory: {
			name: "memory",
			type: "wry::memory:System",
			heaps: {
				name: "stack",
				type: "wry::memory::Heap",
				params: {
					"size": 8196,
					"blockSize": 64
				},
				{	
					name: "heap",
					type: "wry::memory::Heap",
					params: {
						"size": 8196,
						"blockSize": 64
					}
				}
			}
		},
		resources: {
			name: "resources",
			type: "wry::res::System",
			params: {
				watch: true
			},
			filters: [
				{
					key: "locale",
					value: ${default}
				},
				{
					key: "system",
					value: ${default}
				}
			]
			mount: [
				{
					key: "root",
					value: "./"
				}
			]
		}
	}
}	
*/

/* settings
[{
	name: "graphics", 
	values: {
		fullscreen: true,
		colors: 32,
		width: 1024,
		height: 768,
		samples: 1,
		textures: "eGraphicsSetting_High",
		adapter: "AdapterName"
	}
}]
*/

/* startup
[{
	name: "winMain",
	type: "wry::os::Window",
	params: {
		top: 0,
		left: 0,
		width: ${settings[name='graphics'].values.width,
		height: ${settings[name='graphics'].values.height
	}
},
{
	name: "gfxDevice",
	type: "wry::gfx::Device",
	params: {
		"adapter": "${settings[name='graphics'].values.adapter}"
	}
},
{
	name: "gfxContext",
	type: "wry::gfx::RenderContext",
	params: {
		"device": "${startup[name='gfxDevice']}",
		"window": "${startup[name='winMain']}"
	}
}]
*/

//int main(int argv, char** args){
	/*wry::Engine engine("init");

	auto startup = engine.resources().create("startup", engine.memory().stack()); // creates objects in the startup script & force these on the stack
	engine.load(startup);

	while(true) {
		engine.begin();
			engine.doEvents();
			engine.update();
			engine.draw();
			engine.present();
		engine.end();
	}

    return 0;
	*/
//}

void audio() {
	/*
		wry::audio::Mixer 	mixer;
		mixer.play(wry::io::File("file.wav").toMemoryStream());		
	*/
}

void serialization() {
	/*
		JsonSerializer serializer(wry::io::File("file.json").toFileStream());
		Resolver resolver;

		Archive archive(serializer, resolver);

		resolver.resolve(name, interface*);

		ObjectType type = archive.read<ObjectType>();

		serializer.read(name, variable);	//primitive
		serilaizer.read(variable); 			//ISerializable
		serializer.read(name, array); 		//ArrayType
		serializer.read(array); 			//ArrayType

		serializer.write(name, variable);	//primitive
		serializer.write(variable); 		//ISerializable
		serializer.write(name, array); 		//ArrayType
		serializer.write(array); 			//ArrayType

		read(name, primitive &variable) {
			variable = json[name];
		}

		read(name, primitive &variable) {
			stream.read(&variable, sizeof(primitive));
		}
	*/
}


void gfx() {
	/*
		wry::os::Window winMain;
		winMain.width(1024)
			.height(1024)
			.title("Editor Demo");

		wry::gfx::System 		gfxSystem;
		wry::gfx::Device		gfxDevice(gfxSystem.adapter());
	
		wry::gfx::RenderContext gfxContext(gfxDevice, winMain);

		wry::gfx::Resource		gfxVertexBuffer(gfxDevice);
		gfxVertexBuffer.write([ {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}]);

		wry::gfx::ResourceDescriptor gfxVertexInputElement();
		gfxVertexInputElement
			.name("POSITION")
			.format(wry::gfx::eDataFormat_R32G32B32_FLOAT)
			.scope(eDataInputClassification_PerVertex);

		wry::gfx::ResourceDescriptor gfxColorInputElement();
		gfxVertexInputElement
			.name("COLOR")
			.format(wry::gfx::eDataFormat_R32G32B32A32_FLOAT)
			.scope(eDataInputClassification_PerVertex);

		wry::io::File shaderFile("shaders.hlsl");
		wry::io::MemoryStream shaderStream(shaderFile.size());
		shaderFile.read(shaderStream);

		wry::gfx::Shader gfxVertexShader(gfxDevice);
		gfxVertexShader
			.data(shaderStream.data())
			.entry("VSMain")
			.name("shaders")
			.target("vs_5_0");

		wry::gfx::Shader gfxPixelShader(gfxDevice);
		gfxPixelShader
			.data(shaderStream.data())
			.entry("PSMain")
			.name("shaders")
			.target("ps_5_0");

		wry::gfx::RenderState gfxRenderState(gfxDevice);
		gfxRenderState
			.primitiveType(wry::gfx::ePrimitiveType_Triange)
			.descriptors(0, gfxVertexInputElement)
			.descriptors(1, gfxColorInputElement)
			.shaders(eShaderType_Vertex, gfxVertexShader)
			.shaders(eShaderType_Pixel, gfxPixelShader);

		wry::gfx::CommandList gfxCommandList(gfxDevice);
		gfxCommandList.begin();
		{
			gfxCommandList.renderState(gfxRenderState)
				.viewport({0, 0, 1024, 768})
				.scissorRect({0, 0, 1024, 768})
				.vertexBuffers(0, gfxVertexBuffer);

			gfxCommandList.clear({.5, .5, .5, 1.0});
			gfxCommandList.draw(3, 1, 0, 0);
		}
		gfxCommandList.end();

		mainWindow.show();
		bool_t running = true;
		while(running) {
			winMain.update();
			gfxContext.execute(gfxCommandList);
			gfxContext.present();
		}
	*/
}


