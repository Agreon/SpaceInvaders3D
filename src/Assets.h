//
// Created by root on 06.05.16.
//

#ifndef SPACEINVADERS3D_ASSETS_H
#define SPACEINVADERS3D_ASSETS_H

#include <string>
#include <map>
#include <GL/gl.h>
#include <AL/al.h>
#include <AL/alut.h>

using namespace std;

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
/*
class Assets{
public:

        static bool initialize(){
            int error;

            // Init openAL
            alutInit(0, NULL);
            //alutInitWithoutContext(NULL,NULL);
            // Clear Error Code (so we can catch any new errors)
            alGetError();

            // Create the buffers
            alGenBuffers(NUM_BUFFERS, m_Buffers);
            if ((error = alGetError()) != AL_NO_ERROR)
            {
                printf("alGenBuffers : %d", error);
                return false;
            }

        }


        static bool loadSound(string name, string path){
            int error;

            ALuint sndBuffer, state, source;
    // make sure to call alutInitWithoutContext first
            sndBuffer = alutCreateBufferFromFile(path.c_str());
            if ( alutGetError() != ALUT_ERROR_NO_ERROR )
            {
                printf("alutLoadWAVFile exciting_sound.wav : %d", error);
                // handle the error
                return false;
            }

            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, sndBuffer);

            m_Sounds[name] = source;
        }

        static void shutdown(){
            alutExit();
        }

        //External LoadBMP function
        static bool loadTexture(string name, string path){
            // Data read from the header of the BMP file
            unsigned char header[54]; // Each BMP file begins by a 54-bytes header
            unsigned int dataPos;     // Position in the file where the actual data begins
            unsigned int width, height;
            unsigned int imageSize;   // = width*height*3
// Actual RGB data
            unsigned char * data;

            // Open the file
            FILE * file = fopen(path.c_str(),"rb");
            if (!file){printf("Image could not be opened\n"); return 0;}

            if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
                printf("Not a correct BMP file\n");
                return false;
            }

            if ( header[0]!='B' || header[1]!='M' ){
                printf("Not a correct BMP file\n");
                return 0;
            }

            // Read ints from the byte array
            dataPos    = *(int*)&(header[0x0A]);
            imageSize  = *(int*)&(header[0x22]);
            width      = *(int*)&(header[0x12]);
            height     = *(int*)&(header[0x16]);

            // Some BMP files are misformatted, guess missing information
            if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
            if (dataPos==0)      dataPos=54; // The BMP header is done that way

            // Create a buffer
            data = new unsigned char [imageSize];

            // Read the actual data from the file into the buffer
            fread(data,1,imageSize,file);

            //Everything is in memory now, the file can be closed
            fclose(file);

            // Create one OpenGL texture
            GLuint textureID;
            glGenTextures(1, &textureID);

            // "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Give the image to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            m_Textures[name] = textureID;
            return true;
        }
        static void useTexture(string name){

        }

        static void playSound(string name){
            alSourcePlay(m_Sounds[name]);
        }

private:
    static map<string,GLuint> m_Textures;
    static map<string,ALuint> m_Sounds;

    static const int NUM_BUFFERS = 32;

    static ALuint m_Buffers[NUM_BUFFERS];

};
*/
#endif //SPACEINVADERS3D_ASSETS_H
