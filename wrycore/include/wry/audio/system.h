#pragma once

/*

namespace audio {
    class System {
    public:
        System() {}
        virtual ~System() { release(); }
        
        retval<void> init();
        retval<void> release();

        readonly_t<bool_t> initialized() const;

        gsl::span<audio::Device>    devices() const;

        property<Device, uint_t>    default();
        property<f32>               masterVolume();

    protected:
        bool_t                      _initialized;
        std::vector<audio::Device>  _devices;

        f32                         _masterVolume;
        Device*                     _default;
    };

    ENUM(eAudioFrequency, 
        11025 = 11025,
        22050 = 22050,
        44100 = 44100,
        CDQuality = eAudioFrequency_44100
    );

    ENUM(eAudioFormat, 
        u8,
        s8,

        u16_LittleEndian,
        u16_BigEndian,
        u16_SystemDefault,

        s16_LittleEndian,
        s16_BigEndian,
        s16_SystemDefault,
        
        s32_LittleEndian,
        s32_BigEndian,
        s32_SystemDefault,

        f32_LittleEndian,
        f32_BigEndian,
        f32_SystemDefault,

        u16 = eAudioFormat_u16_LittleEndian,
        s16 = eAudioFormat_s16_LittleEndian,
        s32 = eAudioFormat_s32_LittleEndian,
        f32 = eAudioFormat_1f32_LittleEndian
    );

    ENUM(eAudioChannel,
        Default = 0,
        Mono = 1,
        Sterio = 2,
        Quadrophonic = 4,
        Surround51 = 6,
        Surround71 = 8
    );

    struct Specification {
    public:
        property_t<eAudioFrequency> frequency;
        property_t<eAudioFormat> format;
        property_t<eAudioChannels> channels;
        property_t<uint_t> samples;
    };

    class Device {
    public:
        retval<void> init(audio::Specification& desc);
        retval<void> release();

        readonly_t<czstring<>> name() const;

    protected:
        int _index;
    };

    class WAV : public ISound {
    public:
        retval<void> load(io::Stream& stream);
    };

    io::MemoryStream stream;
    io::File("file.wav", eFileOpen_ReadOnly, eFileLock_None)
        .write(stream)
        .close();

    audio::Mixer mixer;
    mixer.play(stream);

    class Mixer {
    public:
        retval<void> play(audio::Buffer& sound);
        retval<void> play(audio::Buffer& sound, audio::Device& device);
    };
}

*/
