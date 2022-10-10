#include "threads.h"
#include <sire.hpp>

threadSimulation::threadSimulation(QThread *parent)
	: QThread(parent)
{
  running = false; // set to stop detached thread(thread_visual)
}

void threadSimulation::run()
{
    num_contacts = 0;
    auto& sim = sire::Simulator::instance("H:/contact/Sire/config/sire.xml");
    auto& collision = sire::Collision::instance("C:/Users/ZHOUYC/Desktop/STL_test");
   
    //��������켣�滮
    sim.SimPlan();
    //�߳�thread_visual��ÿ100ms��sim��ȡlinkλ��  TODO �̻߳���
    static std::thread thread_visual([&] {
        running = true;
        while (num_contacts == 0 && running && !threadStop) {
            //TODO num_contact=0 one time
            auto start = std::chrono::steady_clock::now();
            //��aris_sim��ȡlinkλ��
            sim.GetLinkPQ(link_pq);
            //ͨ��mainwindow.cpp�вۺ�������link_pm��occview.cpp�е�setLinkPm
            emit updateLinkPQ(link_pq); 

            ////�����Ƿ���ײ
            collision.CalCollision(link_pq, num_contacts);
            std::this_thread::sleep_until(start + std::chrono::milliseconds(100));
        }
        });
    //�����߳�thread_visual
    if (thread_visual.joinable()) {
        thread_visual.detach();
    }
}

void threadSimulation::ThreadStart()
{
	QMutexLocker locker(&m_lock);
	threadStop = false;
}

void threadSimulation::ThreadStop()
{
	QMutexLocker locker(&m_lock);
	threadStop = true;
}

 
threadSimulation::~threadSimulation()
{
    running = false; // set to stop detached thread
}














