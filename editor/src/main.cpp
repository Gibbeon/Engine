#include "wry/global.h"
#include "wry/os/windows/window.h"
#include "wry/gfx/gfx.h"

int main(int argv, char** args){
	wry::os::Window winMain;
	winMain.width(1024)
			.height(1024)
			.title("Editor Demo");

	wry::gfx::System 		gfxSystem;
	wry::gfx::Device		gfxDevice(gfxSystem.adapter());


	/*
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

    return 0;
}


