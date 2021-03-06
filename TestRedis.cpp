// TestRedis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <Windows.h>
#include <hiredis.h>
#include <string>

using namespace std;

//#pragma comment(lib, "Win32_Interop.lib")
//#pragma comment(lib, "hiredis.lib")


int main()
{
    std::cout << "Hello World!\n";

    //redis默认监听端口为6387 可以再配置文件中修改 
    redisContext* pRedisContext = redisConnect("127.0.0.1", 6379);
    if (NULL == pRedisContext || pRedisContext->err)
    {
        printf("%s \r\n", pRedisContext->errstr);
        printf("Connect to redis server failed \n");
        return -1;
    }

    //输入Redis密码
    const char* pszRedisPwd = "123456";
    redisReply* pRedisReply = (redisReply*)redisCommand(pRedisContext, "AUTH %s", pszRedisPwd);
    if (NULL != pRedisReply)
    {
        freeReplyObject(pRedisReply);
    }

    //向Redis写入数据
    pRedisReply = (redisReply*)redisCommand(pRedisContext, "SET keyName huantest");
    if (NULL != pRedisReply)
    {
        freeReplyObject(pRedisReply);
    }

    //用get命令获取数据
    char szRedisBuff[256] = { 0 };
    sprintf_s(szRedisBuff, "GET %s", "keyName");
    pRedisReply = (redisReply*)redisCommand(pRedisContext, szRedisBuff);
    if (NULL == pRedisReply)
    {
        printf("Get data Error!");
        return -1;
    }

    if (NULL == pRedisReply->str)
    {
        freeReplyObject(pRedisReply);
        return -1;
    }

    string strRes(pRedisReply->str);
    freeReplyObject(pRedisReply);

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
