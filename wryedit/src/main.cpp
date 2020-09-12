#include "wry/global.h"
#include "wry/gfx.h"
#include "wry/io.h"


#include <functional>
#include <map>

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


int main(int argv, char** args) {
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


