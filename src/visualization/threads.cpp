#include "threads.h"
#include "occview.h"
#include "ui_mainwindow.h"
#include <sire.hpp>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <math.h>

threadSimulation::threadSimulation(QThread *parent)
    : QThread(parent) {
  running = false;// set to stop detached thread(thread_visual)
}

void threadSimulation::run() {

  num_contacts = 0;
  //��������켣�滮
  //auto &sim = sire::Simulator::instance("H:/contact/collision/collision.xml");
//  sire::collision::Collision &collision = sire::collision::Collision::instance("C:/Users/ZHOUYC/Desktop/model_sw/Robot_STL");

  auto &sim = sire::physics::contact::BallRebound::instance();
  std::array<double, 6> track_point;

  if (OccView::finish_norm) {
    //auto track_points = OccView::GetTrackPoints();
    auto CutOver_CAM_pointVecVecs = OccView::GetTrackPoints();
    //track_points ������ӷ����� ת��Ϊ �������ŷ����
    for (auto i: CutOver_CAM_pointVecVecs) {
      for (auto j :i) {
        Eigen::Matrix3d m;
        Eigen::Vector3d zaxis(0, 0, 1);
        Eigen::Vector3d tmpvec(-j.v1.X(), -j.v1.Y(), -j.v1.Z());
        tmpvec.normalize();
        // ��˵õ�ת�ᣬ�����Ǵ�z_axisת��normal
        Eigen::Vector3d rot_axis = zaxis.cross(tmpvec);
        rot_axis.normalize();// ��һ��
        std::cout << "axis: " << rot_axis.transpose() << std::endl;
        // ��˵õ�ת��
        double rot_angle = acos(zaxis.dot(tmpvec));
        std::cout << "angle: " << rot_angle * 180.0 / M_PI << std::endl;
        // �õ���ת����
        Eigen::Matrix3d m_rot = Eigen::Matrix3d(Eigen::AngleAxisd(rot_angle, rot_axis));

        //todo����ӹ��� 
        //      Eigen::Matrix4d m_tool,m_origin;
        //      m_origin.setIdentity();
        //      m_origin.block<3,3>(0,0) = m_rot;
        //      Eigen::Vector3d pos(track_point[0]* 0.001,track_point[1]* 0.001,track_point[2]* 0.001);
        //      m_origin.block<3,1>(0,3) = pos.transpose();
        ////      m_origin << m_rot(0),m_rot(1),m_rot(2),track_point[0]* 0.001,
        ////                  m_rot(3),m_rot(4),m_rot(5),track_point[1]* 0.001,
        ////                  m_rot(6),m_rot(7),m_rot(8),track_point[2]* 0.001,
        ////                  0,0,0,1;
        //      m_tool << 1,0,0,0,
        //                0,1,0,0,
        //                0,0,1,-0.018,
        //                0,0,0,1;
        //      std::cout << "m_origin "<<m_origin << std::endl;
        //      std::cout << "m_tool "<<m_tool << std::endl;
        //      Eigen::Matrix4d m_rot_modify = m_origin * m_tool;
        //      m_rot = m_rot_modify.block<3,3>(0,0);
        //      std::cout << "m_rot_modify "<<m_rot_modify << std::endl;

        // arisĬ��313���õ�ŷ����
        Eigen::Vector3d v_RPY = m_rot.eulerAngles(3, 1, 3);
        //std::cout << "eulerAngle: " << v_RPY.transpose() << std::endl;
        //track_point[0] = m_rot_modify(0,3);
        //track_point[1] = m_rot_modify(1,3);
        //track_point[2] = m_rot_modify(2,3);
        
        track_point[0] = j.p1.X() * 0.001;
        track_point[1] = j.p1.Y() * 0.001;
        track_point[2] = j.p1.Z() * 0.001;
        track_point[3] = v_RPY[0];
        track_point[4] = v_RPY[1];
        track_point[5] = v_RPY[2];
        std::cout << "track_point: " << track_point[0] << " " << track_point[1] << " " << track_point[2]
          << " " << track_point[3] << " " << track_point[4] << " " << track_point[5] << std::endl;
        track_points.push_back(track_point);
      }
    }
    //sim.SimPlan(track_points);
  } else {
    std::cout << "move without normal vertor" << std::endl;
    //sim.SimPlan();
  }

  //�߳�thread_visual��ÿ100ms��sim��ȡlinkλ��
  static std::thread thread_visual([&] {
    running = true;
    const double delta_t = 0.01;
    while (/*num_contacts == 0 &&*/ running && !threadStop) {
      //TODO num_contact=0 one time
      auto start = std::chrono::steady_clock::now();
      //��aris_sim��ȡlinkλ��
      sim.CalContact(sphere_pq, num_contacts);
      //std::cout << "position:"
      //          << "x " << sphere_pq[0] << " y " << sphere_pq[1] << " z " << sphere_pq[2] << std::endl;
      //sim.GetLinkPQ(link_pq);
      //ͨ��mainwindow.cpp�вۺ�������link_pm��occview.cpp�е�setLinkPm()
      //emit updateLinkPQ(link_pq);
      emit updateSpherePQ(sphere_pq);
      //�����Ƿ���ײ
//      collision.CalCollision(link_pq, num_contacts);
      std::this_thread::sleep_until(start + std::chrono::duration<double, std::milli>(delta_t * 1000));

    }
  });
  //�����߳�thread_visual
  if (thread_visual.joinable()) {
    thread_visual.detach();
  }
}

void threadSimulation::ThreadStart() {
  QMutexLocker locker(&m_lock);
  threadStop = false;
}

void threadSimulation::ThreadStop() {
  QMutexLocker locker(&m_lock);
  threadStop = true;
}

threadSimulation::~threadSimulation() {
  running = false;// set to stop detached thread
}
