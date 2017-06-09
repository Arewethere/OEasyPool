/**
* @author : ��³��
* @date   : 2017��04��
* @version: 1.0
* @note   : ���� Apache ���֤ 2.0 �棨���¼�ơ����֤������Ȩ;
*           �������ر���ɣ�����������ʹ������ļ���
* @remarks: �����Ի�ø���ɵĸ�����
*           http://www.apache.org/licenses/LICENSE-2.0
*           �������÷�����Ҫ��������ͬ�⣬������ɷַ������
*           Ҫ����ԭ�����ַ���û���κ���ʽ�ģ���ȷ�������ĵ������
*           �μ����ձ���ɿ������Ȩ�޼����Ƶ��ض����Ե����֤��
*
*   ����Ի�øô�������°汾��
*
*        http://git.oschina.net/Mr_ChenLuYong/oeasypool
*
*   ��Դ�����������˶��ڴ�����Ĺ�ͬά����
*
*
*   ��������Щ���뻹�в����ĵط�����ͨ�����µ����½���ѧϰ��
*
*        ���͵�ַ��http://blog.csdn.net/csnd_ayo
*
*        ���µ�ַ��http://blog.csdn.net/csnd_ayo/article/details/72457190
*
* 	 �ڴ����ύBug����ӭIssues��
*
*/

#include <time.h>
#include <iostream>
#include <memory>
#include <string>
#include "OE/EasyThreadPool"

#include "../../test/OEFunctionTask.h"



using namespace std;



int vFunction(void) {
    std::cout << __FUNCTION__ << std::endl;
    return 0;
}


int hello(int a, std::string b) {
    std::cout << __FUNCTION__ << " " << a << ":" << b << std::endl;
    return 0;
}

      
int main(void)
{
    OEThreadPool::ThreadPoolConfig threadPoolConfig;
    threadPoolConfig.nMaxThreadsNum = 100;
    threadPoolConfig.nMinThreadsNum = 5;
    threadPoolConfig.dbTaskAddThreadRate = 3;
    threadPoolConfig.dbTaskSubThreadRate = 0.5;
    clock_t start = clock();
    {

        std::shared_ptr<OEThreadPool> threadPool(new OEThreadPool);
        threadPool->init(threadPoolConfig);

        int i = 0;
        while (true)
        {
            
            //std::shared_ptr<OEFunctionTask> request(new OEFunctionTask(vFunction));

            //threadPool->addTask(request);


            std::shared_ptr<OEFunctionTask> request2(new OEFunctionTask);
            request2->asynBind(hello, i++, std::string("http://blog.csdn.net/csnd_ayo/article/details/72457190"));

            threadPool->addTask(request2);

            //            if (request->getID() == 101000) {
            //				break;
            //            }
        }

        threadPool->release();
    }
    clock_t finish = clock();
    std::cout << "duration:" << finish - start << "ms" << std::endl;
    getchar();
    return 0;
}

