
inline const char* getHelloWorld() {
    return "Goodbye World\n";
}

/*
core\
    kernel.h

    serialization\
        archive.h
        serializable.h

        impl\
            json.h
            binary.h
            xml.h

    reflection\
        enum.h
        type.h
        activator.h

    math\
        vec2.h
        vec3.h
        vec4.h
        mat2x2.h
        mat3x3.h
        mat4x4.h
        quat.h

    rendering\
        adapter.h
        device.h
        state.h
        context.h

        buffers\
            buffer.h
            vertex.h
            index.h
            hull.h
            geo.h
        
        resources\
            texture.h

        fragments\
            shader.h

    gfx\
        light.h
        texture.h
        material.h

        // probably more in engine
        sprite.h
        mesh.h
        viewport.h
        camera.h

    animation\
        blender.h
        keyframe.h

    memory\
        heap.h

        impl\
            malloc.h
            
    io\
        file.h
        path.h
        stream.h

        compression\
            zlib.h

        devices\
            keyboard.h
            mouse.h
            controller.h
            joystick.h

    audio\
        mixer.h
        sound.h

        formats\
            wav.h
            mp3.h
    
    video\
        player.h

        formats\
            mov.h

    math\
        mat4x4.h
        mat3x3.h
        mat2x2.h

        quat.h
        
        vec2.h
        vec3.h
        vec4.h

        rect.h
        circle.h
        sphere.h
        box.h

    os\
        window.h
        system.h
        environment.h

    threading\
        thread.h
        task.h
        parallel.h

    debug\
        logger.h
        profiler.h
        debugger.h

    time\
        clock.h
        timespan.h
        time.h

engine\
    resources\
    scene\
        
    input\
        inputmapper.h

    config\
        gfx.h
        video.h
    
*/
