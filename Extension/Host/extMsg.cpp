#include <iostream>
#include <string>
#include <windows.h>
#include <stdint.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <future>
#include <ctime>

struct _data{
	union{
		char ch[4];
		uint32_t ulen;
	};
}data;

volatile bool g_bFlag = true;

int threadfeedback(uint32_t uIndex)
{
	while(g_bFlag)
	{
		
		std::string strRes;
		if(uIndex == 0)
		{
			std::srand(std::time(nullptr));
			std::this_thread::sleep_for(std::chrono::seconds(2+std::rand()%3));
			strRes = "{\"response\": \"1 welcome connect\"}";
		}
		else if(uIndex == 1)
		{
			std::srand(std::time(nullptr));
			std::this_thread::sleep_for(std::chrono::seconds(1+std::rand()%5));
			strRes = "{\"response\": \"2 welcome connect\"}";
		}
		uint32_t uLength = strRes.size();
		char szRes[4];
		memcpy(szRes, &uLength, sizeof(uint32_t));
		data.ulen = strRes.size();
		//std::cout.write(data.ch, sizeof(data));
		std::cout.write(szRes, sizeof(uint32_t));
		std::cout.write(strRes.c_str(), strRes.size());
		std::cout.flush();
	}
	return 1000;
}

int main()
{

	std::future<int> t2 = std::async(std::launch::async, threadfeedback, 1);
	std::thread t1(threadfeedback, 0);

	while(1)
	{
		
		
		char szLen[4] = {0};
		std::cin.read(szLen, 4);
		std::string strMsg = szLen;
		if(strMsg.length() == 0)
		{
			g_bFlag = false;
			break;
		}
		
		std::stringstream ss;
		ss << (uint32_t)szLen[3] << (uint32_t)szLen[2] << (uint32_t)szLen[1] << (uint32_t)szLen[0];
		//::MessageBoxA(NULL, ss.str().c_str(), "Length", MB_OK);
		
		uint32_t uLen = (uint32_t)(std::stoi(ss.str()));
		//::MessageBoxA(NULL, ss.str().c_str(), "Length", MB_OK);

		if(uLen > 0)
		{
			char* pMsg = new char[uLen+1];
			::memset(pMsg, 0, uLen+1);

			std::cin.read(pMsg, uLen);
			std::string strMsg = pMsg;
			//::MessageBoxA(NULL, strMsg.c_str(), "Message", MB_OK);
			delete []pMsg;




			std::string strRes = "{\"response\": \"welcome message\"}";
			//std::string strRes = "{\"response\": \"" + strRes + "\"}";
			uint32_t uLength = strRes.size();
			char szRes[4];
			memcpy(szRes, &uLength, sizeof(uint32_t));
			data.ulen = strRes.size();
			//std::cout.write(data.ch, sizeof(data));
			std::cout.write(szRes, sizeof(uint32_t));
			std::cout.write(strRes.c_str(), strRes.size());
			std::cout.flush();
			

		}
		else
		{
			::Sleep(1);
		}
	}
	
	t1.join();
	t2.get();


	return 1;
}