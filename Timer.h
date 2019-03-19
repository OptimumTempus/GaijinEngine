#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<time.h>
#include<windows.h>
#include<string>
#include"Text.h"



namespace Utils
{
	class Timer
	{

	public:
		Timer()
		{
			t = 0;
			dt = 0.0;
			curTime = 0.0;
			lastTime = 0.0;
			frameCount = 0;


			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			t_frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&t_Start);
		}

		inline void reset()
		{
			QueryPerformanceCounter(&t_Start);
		}

		inline float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned _int64 cycles = current.QuadPart - t_Start.QuadPart;
			return(float)(cycles * t_frequency);

		}


		inline float updateDT()
		{
			curTime = static_cast<float>(glfwGetTime());
			dt = curTime - lastTime;
			lastTime = curTime;
			return dt;
		};

		inline void runFPSCounter(int* frame)
		{
			frameCount++;
			if ((this->elapsed() - t) > 1.0)
			{
				t += 1.0f;
				*frame = frameCount;
				//std::cout << frameCount << std::endl;
				frameCount = 0;
				
			}
		};

		inline std::string getFrameCount()
		{
			return std::to_string(frameCount);
		}

		inline int getFrameCounter()
		{
			return this->frameCount;
		};

		inline void setT(float a)
		{
			t += a;
		}

		inline float getT()
		{
			return this->t;
		};

		inline float returnDT()
		{
			return this->dt;
		};

		inline float returnCurTime()
		{
			return curTime;
		}

	private:
		int frameCount;

		float dt;
		float curTime;
		float lastTime;
		float t;

		LARGE_INTEGER t_Start;
		double t_frequency;
	};
}