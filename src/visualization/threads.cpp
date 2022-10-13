#include "threads.h"
#include "occview.h"
#include <sire.hpp>
#include "ui_mainwindow.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <math.h>

threadSimulation::threadSimulation(QThread *parent)
	: QThread(parent)
{
//  auto occWidget1_t = new OccView();
  running = false; // set to stop detached thread(thread_visual)
}

void threadSimulation::run()
{
  num_contacts = 0;
//  auto& collision = sire::Collision::instance("C:/Users/ZHOUYC/Desktop/STL");

  //��������켣�滮
  auto& sim = sire::Simulator::instance("H:/contact/Sire/config/sire.xml");
  if(OccView::finish_norm){
    auto track_points = OccView::GetTrackPoints();
    std::cout<<"fucking number"<<M_PI<<track_points[1][1]<<std::endl;
    //track_points������ӷ����� ת��Ϊ �������ŷ����
    for(auto &track_point : track_points){
      Eigen::Matrix3d m;
      Eigen::Vector3d zaxis(0, 0, 1);
      Eigen::Vector3d tmpvec(-track_point[3], -track_point[4], -track_point[5]);
      tmpvec.normalize();
      // ��˵õ�ת�ᣬ�����Ǵ�z_axisת��normal
      Eigen::Vector3d rot_axis = zaxis.cross(tmpvec);
      rot_axis.normalize(); // ��һ��
      std::cout<<"axis: "<<rot_axis.transpose()<<std::endl;
      // ��˵õ�ת��
      double rot_angle = acos(zaxis.dot(tmpvec));
      std::cout<<"angle: "<<rot_angle*180.0/M_PI<<std::endl;
      // �õ���ת����
      Eigen::Matrix3d m_rot = Eigen::Matrix3d(Eigen::AngleAxisd(rot_angle, rot_axis));
      // arisĬ��313���õ�ŷ����
      Eigen::Vector3d v_RPY = m_rot.eulerAngles(3,1,3);
      std::cout<<"eulerAngle: "<<v_RPY.transpose()<<std::endl;
      track_point[0] = track_point[0]*0.001;
      track_point[1] = track_point[1]*0.001;
      track_point[2] = track_point[2]*0.001;
      track_point[3] = v_RPY[0];
      track_point[4] = v_RPY[1];
      track_point[5] = v_RPY[2];
    }
    sim.SimPlan(track_points);
  }else{
    std::cout<<"move without normal vertor"<<std::endl;
    sim.SimPlan();
  }



    //�߳�thread_visual��ÿ100ms��sim��ȡlinkλ��
    static std::thread thread_visual([&] {
        running = true;
        while (num_contacts == 0 && running && !threadStop) {
            //TODO num_contact=0 one time
            auto start = std::chrono::steady_clock::now();
            //��aris_sim��ȡlinkλ��
            sim.GetLinkPQ(link_pq);
            //ͨ��mainwindow.cpp�вۺ�������link_pm��occview.cpp�е�setLinkPm()
            emit updateLinkPQ(link_pq); 

            ////�����Ƿ���ײ
//            collision.CalCollision(link_pq, num_contacts);
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
//    delete occWidget_t;
}














