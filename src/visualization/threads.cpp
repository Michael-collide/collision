#include "threads.h"
#include <aris_sim.hpp>

threadSimulation::threadSimulation(QThread *parent)
	: QThread(parent)
{
  aris_sim::InitSimulator();
  aris_sim::InitCollision("C:/Users/ZHOUYC/Desktop/ee_5.STL");
  num_contacts = 0;
  running = false; // set to stop detached thread(thread_visual)
}

void threadSimulation::run()
{
    num_contacts = 0;
    //��������켣�滮
    aris_sim::SimPlan();
    //�߳�thread_visual��ÿ100ms��sim��ȡlinkλ��  TODO �̻߳���
    static std::thread thread_visual([&] {
        running = true;
        while (num_contacts == 0 && running && !threadStop) {
            //TODO num_contact=0 one time
            auto start = std::chrono::steady_clock::now();
            //��aris_sim��ȡlinkλ��
            aris_sim::DynamicSimulator(link_pm);
            //ͨ��mainwindow.cpp�вۺ�������link_pm��occview.cpp�е�setLinkPm
            emit updateLinkPm(link_pm);

            px = link_pm[6 * 16 + 3];
            py = link_pm[6 * 16 + 7];
            pz = link_pm[6 * 16 + 11];
            // std::cout << "position:" << "px " << px << " py " << py << " pz " << pz << std::endl;
            //�����Ƿ���ײ
            //TODO ƽ��+��ת
            aris_sim::Collision(float(px), float(py), float(pz), num_contacts);
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














