//
// Created by root on 06.05.16.
//

#ifndef SPACEINVADERS3D_ASSETS_H
#define SPACEINVADERS3D_ASSETS_H

#include <string>
#include <map>
#include <GL/gl.h>

#ifdef _WIN32
#include <Windows.h>
#include <Mmsystem.h>

namespace Assets{

	map<string, string> m_Sounds;

	bool initialize(){
		return true;
	}

	void shutdown(){}

	bool loadSound(string name, string path){
		m_Sounds[name] = path;
		return true;
	}

	void playSound(string name){
		cout << "Playing sound " << name << endl;
		PlaySound(TEXT(m_Sounds[name].c_str()), NULL, SND_FILENAME | SND_ASYNC);

	}

	void stopSound(string name){
		cout << "Playing sound " << name << endl;
	}

};

#else

#include <AL/al.h>
#include <AL/alut.h>

using namespace std;

/*
 * "Static" Asset class at the moment only for playing sounds
 */
namespace Assets{

	map<string,GLuint> m_Textures;
    map<string,ALuint> m_Sounds;

    bool initialize(){

        //alutInit(0, NULL);
       alutInitWithoutContext(NULL,NULL);    //TODO: Ausprobieren falls es nicht klappt
        alGetError();

        ALCcontext *context;
        ALCdevice *device;

        device = alcOpenDevice(NULL);
        if (device == NULL)
        {
            cout << "Could not create device" << endl;
            return false;
        }

        context = alcCreateContext(device,NULL);
        alcMakeContextCurrent(context);
		return true;
    }

    /*
     * TODO: 1 size is maybe not variable
     */
    void shutdown(){
        for(auto& sound : m_Sounds){
            alDeleteSources(1, &sound.second);
        }

        ALCcontext *context = alcGetCurrentContext();

        ALCdevice *device = alcGetContextsDevice(context);

        alcMakeContextCurrent(NULL);

        alcDestroyContext(context);

        alcCloseDevice(device);

        alutExit();
    }

    bool loadSound(string name, string path){

        ALuint buffer, source;

        //https://wiki.delphigl.com/index.php/alutCreateBufferFromFile
        buffer = alutCreateBufferFromFile(path.c_str());
        if(buffer == AL_NONE)
        {
            cout << "ERROR while loading file: " << name << endl;
            cout << alutGetErrorString(alutGetError()) << endl;
            return false;
        }

        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);

        cout << "Loaded Sound " << name << endl;

        m_Sounds[name] = source;
		return true;
    }

    void playSound(string name){
        cout << "Playing sound " << name << endl;
        alSourcePlay(m_Sounds[name]);
    }

    void stopSound(string name){
        cout << "Playing sound " << name << endl;
        alSourceStop(m_Sounds[name]);
    }

}

#endif
#endif //SPACEINVADERS3D_ASSETS_H
