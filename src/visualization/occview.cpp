﻿#include "occview.h"
#include <aris_sim.hpp>

// #define ER100
#define XB4

#ifdef UR5
double OccView::Joint01CurrentAngle = -PI / 2;
double OccView::Joint02CurrentAngle = -PI / 2;
double OccView::Joint03CurrentAngle = 0.0;
double OccView::Joint04CurrentAngle = -PI / 2;
double OccView::Joint05CurrentAngle = 0.0;
double OccView::Joint06CurrentAngle = 0.0;

#endif

#ifdef KR16
double OccView::Joint01CurrentAngle = 0.0;
double OccView::Joint02CurrentAngle = 0.0;
double OccView::Joint03CurrentAngle = 0.0;
double OccView::Joint04CurrentAngle = 0.0;
double OccView::Joint05CurrentAngle = 0.0;
double OccView::Joint06CurrentAngle = 0.0;
#endif

#ifdef ER100
double OccView::Joint01CurrentAngle = 0.0;
double OccView::Joint02CurrentAngle = 0.0;
double OccView::Joint03CurrentAngle = 0.0;
double OccView::Joint04CurrentAngle = 0.0;
double OccView::Joint05CurrentAngle = 0.0;
double OccView::Joint06CurrentAngle = 0.0;
#endif

#ifdef XB4
double OccView::Joint01CurrentAngle = 0.0;
double OccView::Joint02CurrentAngle = 0.0;
double OccView::Joint03CurrentAngle = 0.0;
double OccView::Joint04CurrentAngle = 0.0;
double OccView::Joint05CurrentAngle = 0.0;
double OccView::Joint06CurrentAngle = 0.0;
double OccView::Joint01OriginAngle_static = 0.0;
double OccView::Joint02OriginAngle_static = 0.0;
double OccView::Joint03OriginAngle_static = 0.0;
double OccView::Joint04OriginAngle_static = 0.0;
double OccView::Joint05OriginAngle_static = 0.0;
double OccView::Joint06OriginAngle_static = 0.0;
#endif



OccView::OccView(QWidget* parent) : QWidget(parent)
{
	//aris_sim::InitSimulator();
	//aris_sim::InitCollision("C:/Users/ZHOUYC/Desktop/ee_5.STL");
	//num_contacts = 0;
	//running = false; // set to stop detached thread(thread_visual)

	InitView();
	//InitFilters();
	m_contextMenu = new QMenu(this);  //这是右击弹出的菜单Fhome
	m_addAction = new QAction("new", this);
	m_delAction = new QAction("delete", this);
	//给菜单添加菜单项
	m_contextMenu->addAction(m_addAction);
	m_contextMenu->addAction(m_delAction);
	QObject::connect(m_addAction, &QAction::triggered, this, [=] {
		getShape();
		displayNormalVector();
		});
	QObject::connect(m_delAction, &QAction::triggered, this, [=] {
		removeNormalVector();
		});

	KukaAx1 = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	KukaAx2 = gp_Ax1(gp_Pnt(260, 0, 675), gp_Dir(0, 1, 0));
	KukaAx3 = gp_Ax1(gp_Pnt(260, 0, 1355), gp_Dir(0, 1, 0));
	KukaAx4 = gp_Ax1(gp_Pnt(662, 0, 1320), gp_Dir(1, 0, 0));
	KukaAx5 = gp_Ax1(gp_Pnt(930, 0, 1320), gp_Dir(0, 1, 0));
	KukaAx6 = gp_Ax1(gp_Pnt(1088, 0, 1320), gp_Dir(1, 0, 0));


	ER100_3000Ax1 = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1));
	ER100_3000Ax2 = gp_Ax1(gp_Pnt(260, 0, 645.5), gp_Dir(0, 1, 0));
	ER100_3000Ax3 = gp_Ax1(gp_Pnt(260, 0, 645.4 + 1150), gp_Dir(0, 1, 0));
	ER100_3000Ax4 = gp_Ax1(gp_Pnt(260 + 1600, 0, 645.4 + 1150 + 230), gp_Dir(-1, 0, 0));
	ER100_3000Ax5 = gp_Ax1(gp_Pnt(260 + 1600, 0, 645.4 + 1150 + 230), gp_Dir(0, 1, 0));
	ER100_3000Ax6 = gp_Ax1(gp_Pnt(260 + 1600 + 214, 0, 645.4 + 1150 + 230), gp_Dir(-1, 0, 0));



	UR5Ax1 = gp_Ax1(gp_Pnt(0, -70.5, 89.2), gp_Dir(0, -1, 0));
	UR5Ax2 = gp_Ax1(gp_Pnt(0, -141, 154.4), gp_Dir(0, 0, 1));
	UR5Ax3 = gp_Ax1(gp_Pnt(0, -75.8, 508.9), gp_Dir(0, 1, 0));
	UR5Ax4 = gp_Ax1(gp_Pnt(0, -68.8, 901.33), gp_Dir(0, -1, 0));
	UR5Ax5 = gp_Ax1(gp_Pnt(0, -116.3, 946.83), gp_Dir(0, 0, 1));
	UR5Ax6 = gp_Ax1(gp_Pnt(0, -161.8, 994.33), gp_Dir(0, -1, 0));

	XB4Ax1 = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	XB4Ax2 = gp_Ax1(gp_Pnt(0.040, 0, 0.342), gp_Dir(0, 1, 0));
	XB4Ax3 = gp_Ax1(gp_Pnt(0.040, 0, 0.617), gp_Dir(0, 1, 0));
	XB4Ax4 = gp_Ax1(gp_Pnt(0.040, 0, 0.642), gp_Dir(1, 0, 0));
	XB4Ax5 = gp_Ax1(gp_Pnt(0.320, 0, 0.642), gp_Dir(0, 1, 0));
	XB4Ax6 = gp_Ax1(gp_Pnt(0.393, 0, 0.642), gp_Dir(1, 0, 0));

	OccProgressIndicator* indicat = new OccProgressIndicator();
	QObject::connect(indicat, SIGNAL(updateProgress(int)), this, SLOT(importValue(int)));

#ifdef UR5
	GeneralAx1 = UR5Ax1;
	GeneralAx2 = UR5Ax2;
	GeneralAx3 = UR5Ax3;
	GeneralAx4 = UR5Ax4;
	GeneralAx5 = UR5Ax5;
	GeneralAx6 = UR5Ax6;
#endif

#ifdef KR16
	GeneralAx1 = KukaAx1;
	GeneralAx2 = KukaAx2;
	GeneralAx3 = KukaAx3;
	GeneralAx4 = KukaAx4;
	GeneralAx5 = KukaAx5;
	GeneralAx6 = KukaAx6;
#endif

#ifdef ER100
	GeneralAx1 = ER100_3000Ax1;
	GeneralAx2 = ER100_3000Ax2;
	GeneralAx3 = ER100_3000Ax3;
	GeneralAx4 = ER100_3000Ax4;
	GeneralAx5 = ER100_3000Ax5;
	GeneralAx6 = ER100_3000Ax6;
#endif

#ifdef XB4
	GeneralAx1 = XB4Ax1;
	GeneralAx2 = XB4Ax2;
	GeneralAx3 = XB4Ax3;
	GeneralAx4 = XB4Ax4;
	GeneralAx5 = XB4Ax5;
	GeneralAx6 = XB4Ax6;
#endif



	//        STEPCAFControl_Reader reader;
	//        reader.SetColorMode(true);
	//        reader.SetNameMode(true);
	//        IFSelect_ReturnStatus status = reader.ReadFile(aFilePath.toUtf8());
	//        Handle(XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
	//        Handle(TDocStd_Document) doc;
	//        anApp->NewDocument("MDTV-XCAF", doc);
	//        bool yes = reader.Transfer(doc);
	//        if (yes)
	//        {

	//            TDF_Label mainLabel = doc->Main();
	//            Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
	//            Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);

	//            {
	//                TDF_LabelSequence tdfLabels;
	//                ShapeTool->GetFreeShapes(tdfLabels);   //获取装配体和组件对应名称
	//                int Roots = tdfLabels.Length();
	//                Assemly_Node * RootNode = AssemlyTree.GetRootNode();
	//                for (int index = 1; index <= Roots; index++)
	//                {
	//                    TDF_Label Label = tdfLabels.Value(index);
	//                    Assemly_Data AssemlyData = GetData(ShapeTool, ColorTool, Label, TopLoc_Location());
	//                    Assemly_Node * Node = AssemlyTree.AddNode(RootNode, AssemlyData);
	//                    MakeTree(ShapeTool, ColorTool, Label, TopLoc_Location(), Node, AssemlyTree);
	//                }
	//            }
	//        }

}

OccView::~OccView() noexcept {
	//running = false; // set to stop detached thread
}

void OccView::paintEvent(QPaintEvent*)
{
	m_view->Redraw();
}

void OccView::resizeEvent(QResizeEvent*)
{
	if (!m_view.IsNull())
	{
		m_view->MustBeResized();
	}
}

QPaintEngine* OccView::paintEngine() const
{
	return nullptr;
}

void OccView::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton)//平移
	{
		if (qApp->keyboardModifiers() == Qt::ShiftModifier) {
			m_context->ShiftSelect(true);

			if (getNewToolCoordinate()) {
				newToolCoordinate();
			}

			if (getNewPartCoordinate()) {
				newPartCoordinate();
			}

			if (selectFirstCurve) {
				startSelectFirstCurve();
			}
			if (selectSecondCurve) {
				startSelectSecondCurve();
			}
			if (selectFaces) {
				startSelectPlains();
			}

		}
		else if (qApp->keyboardModifiers() == Qt::ControlModifier) {
			if (this->getDrawLine()) {
				leftButON = BUTTON_ON;
				myPntStart = Ui::ConvertClickToPoint(event->pos().x(), event->pos().x(), m_view);
			}
		}
		else {
			m_current_mode = CurAction3d_DynamicPanning;
			m_x_max = event->pos().x(); //记录起始X位置
			m_y_max = event->pos().y(); //记录起始Y位置
		}
	}

	if (event->buttons() == Qt::MidButton)  //旋转
	{
		m_current_mode = CurAction3d_DynamicRotation;
		m_view->StartRotation(event->pos().x(), event->pos().y());
	}

	if (event->buttons() == Qt::RightButton) {
		m_contextMenu->exec(event->globalPos());
	}

}

void OccView::mouseReleaseEvent(QMouseEvent* event)
{
	m_current_mode = CurAction3d_Nothing;
	leftButON = BUTTON_OFF;
}

void OccView::mouseMoveEvent(QMouseEvent* event)
{
	switch (m_current_mode)
	{
	case CurAction3d_DynamicPanning:
		//执行平移
		m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
		m_x_max = event->pos().x();
		m_y_max = event->pos().y();
		break;
	case CurAction3d_DynamicRotation:
		//执行旋转
		m_view->Rotation(event->pos().x(), event->pos().y());
		break;
	case CurAction3d_Nothing:
		m_context->MoveTo(event->x(), event->y(), m_view, true);
	}

	const QPoint currPos = this->mapFromGlobal(event->globalPos());
	const QPoint prevPos = m_prevPos;
	m_prevPos = currPos;
	// emit mouseMovedSignal(currPos);

	if (this->getDrawLine() && leftButON) {
		myPntEnd = Ui::ConvertClickToPoint(event->pos().x(), event->pos().y(), m_view);
		Ui::DrawLineByMouse(myPntStart, myPntEnd, PartAISShape, m_context);
	}
}

void OccView::wheelEvent(QWheelEvent* event)
{
	m_view->StartZoomAtPoint(event->pos().x(), event->pos().y());
	m_view->ZoomAtPoint(0, 0, event->angleDelta().y(), 0); //执行缩放
}

void OccView::loadDisplayRobotWhole()
{
	//load the file
	//    STEPControl_Reader reader;
	//    IFSelect_ReturnStatus stat = reader.ReadFile(workpiecePath.toUtf8());
	//    switch (stat)
	//    {
	//    case IFSelect_RetVoid:
	//        std::cout << "normal execution which created nothing, or no data to process!" << std::endl;
	//        break;
	//    case IFSelect_RetDone:
	//        break;
	//    case IFSelect_RetError:
	//        std::cout << "error in command or input data, no execution!" << std::endl;
	//        break;
	//    case IFSelect_RetFail:
	//        std::cout << "execution was run and has failed!" << std::endl;
	//        break;
	//    case IFSelect_RetStop:
	//        std::cout << "indicates end or stop (such as Raise)!" << std::endl;
	//        break;
	//    default:
	//        break;
	//    }
	//    if (stat != IFSelect_RetDone)
	//        return;

	//    //Selecting STEP entities for translation : The whole file
	//    //加载文件
	//    Standard_Integer NbRoots = reader.NbRootsForTransfer();
	//    Standard_Integer num = reader.TransferRoots();

	//    //Mapping STEP entities to Open CASCADE Technology shapes
	//    PartTopoShape = reader.OneShape();
	//    auto number=reader.NbShapes();
	//    qDebug()<<"NbRoots:"<< NbRoots;
	//    qDebug()<<"num:"<< num;
	//    qDebug()<<"number:"<< number;



	//    qDebug()<<"position:"<<  PartTopoShape.Location().Transformation().TranslationPart().X()<<","<<  PartTopoShape.Location().Transformation().TranslationPart().Y()<<","<<  PartTopoShape.Location().Transformation().TranslationPart().Z();


	//    gp_Vec vec(100,110,120);
	//    gp_Trsf rsf01;
	//    rsf01.SetTranslationPart(vec);
	//    TopLoc_Location loc(rsf01);
	//    PartTopoShape.Move(loc);


	//    qDebug()<<"position01:"<<  PartTopoShape.Location().Transformation().TranslationPart().X()<<","<<  PartTopoShape.Location().Transformation().TranslationPart().Y()<<","<<  PartTopoShape.Location().Transformation().TranslationPart().Z();


	STEPCAFControl_Reader readercaf;
	readercaf.SetColorMode(true);
	readercaf.SetNameMode(true);
	IFSelect_ReturnStatus status = readercaf.ReadFile(robotPath.toUtf8());
	qDebug() << "status:" << status;
	Handle(XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
	Handle(TDocStd_Document) doc;

	anApp->NewDocument("MDTV-XCAF", doc);
	qDebug() << "Transfer:" << "1";
	bool yes = readercaf.Transfer(doc);
	qDebug() << "Transfer:" << "2";
	qDebug() << "Transfer:" << yes;
	ocaf = new OCAFBrowser(doc);
	{
		TDF_Label mainLabel = doc->Main();
		Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
		Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
		TDF_LabelSequence tdfLabels;
		ShapeTool->GetFreeShapes(tdfLabels);   //获取装配体和组件对应名称
		int Roots = tdfLabels.Length();
		qDebug() << "Roots:" << Roots;


		TDF_Label Label = tdfLabels.Value(1);
		TDF_LabelSequence components;
		ShapeTool->GetComponents(Label, components);
		qDebug() << "components:" << components.Length();

		for (int i = 1; i <= components.Length(); i++) {
			TDF_Label Label00 = components.Value(i);
			auto shape = ShapeTool->GetShape(Label00);
			RobotAISShape[i - 1] = new AIS_Shape(shape);
			m_context->Display(RobotAISShape[i - 1], true);
		}

		TDF_Label testlabel = components.Value(2);

		//        TopLoc_Location ttloc(tttrsf);
		//        auto tttshape=ShapeTool->GetShape(testlabel);
		//        tttshape.Move(ttloc);



		gp_Trsf delta;
		gp_Vec deltavec(0, 0, 0);
		delta.SetTranslationPart(deltavec);
		tttrsf = tttrsf * delta;

		m_context->SetLocation(RobotAISShape[1], delta);
		m_context->Update(RobotAISShape[1], Standard_True);

		Handle_AIS_ConnectedInteractive aiscon = new AIS_ConnectedInteractive;
		aiscon->Connect(RobotAISShape[5], delta);
		aiscon->SetOwner(RobotAISShape[4]);
		if (aiscon->HasConnection()) {
			auto gg = aiscon->HasConnection();
			qDebug() << "aiscon->HasConnection" << gg;
		}
		delta = delta * delta;
		aiscon->Redisplay(true);
		m_context->Update(RobotAISShape[5], Standard_True);

		m_context->SetLocation(RobotAISShape[4], delta);
		m_context->Update(RobotAISShape[4], Standard_True);

		//取消 robot 模型树
		//RobotAISShape[6]->AddChild(RobotAISShape[7]);
		//RobotAISShape[5]->AddChild(RobotAISShape[6]);
		//RobotAISShape[4]->AddChild(RobotAISShape[5]);
		//RobotAISShape[3]->AddChild(RobotAISShape[4]);
		//RobotAISShape[2]->AddChild(RobotAISShape[3]);
		//RobotAISShape[1]->AddChild(RobotAISShape[2]);
		//RobotAISShape[0]->AddChild(RobotAISShape[1]);

	}

	initRobot();
}

void OccView::initRobot()
{
#ifdef UR5
	Joint01OriginAngle = getJoint01CurrentAngle();
	Joint02OriginAngle = getJoint02CurrentAngle();
	Joint03OriginAngle = getJoint03CurrentAngle();
	Joint04OriginAngle = getJoint04CurrentAngle();
	Joint05OriginAngle = getJoint05CurrentAngle();
	Joint06OriginAngle = getJoint06CurrentAngle();

	double initAngles[6]{ -91.71,-98.96,-126.22,-46.29,91.39,-1.78 };
	for (int k = 0; k < 6; k++) {
		initAngles[k] = initAngles[k] * PI / 180;
	}
	auto angle01 = initAngles[0] - Joint01OriginAngle;
	auto angle02 = initAngles[1] - Joint02OriginAngle;
	auto angle03 = initAngles[2] - Joint03OriginAngle;
	auto angle04 = initAngles[3] - Joint04OriginAngle;
	auto angle05 = initAngles[4] - Joint05OriginAngle;
	auto angle06 = initAngles[5] - Joint06OriginAngle;

	getJoint01CurrentAngle() = angle01 + Joint01OriginAngle;
	getJoint02CurrentAngle() = angle02 + Joint02OriginAngle;
	getJoint03CurrentAngle() = angle03 + Joint03OriginAngle;
	getJoint04CurrentAngle() = angle04 + Joint04OriginAngle;
	getJoint05CurrentAngle() = angle05 + Joint05OriginAngle;
	getJoint06CurrentAngle() = angle06 + Joint06OriginAngle;


	gp_Trsf trans;
	trans.SetRotation(GeneralAx1, angle01);
	m_context->SetLocation(RobotAISShape[1], trans);

	trans.SetRotation(GeneralAx2, angle02);
	m_context->SetLocation(RobotAISShape[2], trans);

	trans.SetRotation(GeneralAx3, angle03);
	m_context->SetLocation(RobotAISShape[3], trans);

	trans.SetRotation(GeneralAx4, angle04);
	m_context->SetLocation(RobotAISShape[4], trans);

	trans.SetRotation(GeneralAx5, angle05);
	m_context->SetLocation(RobotAISShape[5], trans);

	trans.SetRotation(GeneralAx6, angle06);
	m_context->SetLocation(RobotAISShape[6], trans);

	m_context->UpdateCurrentViewer();
#endif // UR5

#ifdef ER100
	Joint01OriginAngle = 0.0;
	Joint02OriginAngle = 0.0;
	Joint03OriginAngle = 0.0;
	Joint04OriginAngle = 0.0;
	Joint05OriginAngle = 0.0;
	Joint06OriginAngle = 0.0;


	/******求解末端tool0坐标矩阵******/
	double jointTool0[6]{ Joint01OriginAngle * PI / 180,
						  Joint02OriginAngle * PI / 180,
						  Joint03OriginAngle * PI / 180,
						  Joint04OriginAngle * PI / 180,
						  Joint05OriginAngle * PI / 180,
						  Joint06OriginAngle * PI / 180 };

	robot_tool0_matrix = Ui::ESTUN_ER100_3000_MDH_Forward(jointTool0);

	robot_tool0_matrix(0, 3) = robot_tool0_matrix(0, 3) * 1000;
	robot_tool0_matrix(1, 3) = robot_tool0_matrix(1, 3) * 1000;
	robot_tool0_matrix(2, 3) = robot_tool0_matrix(2, 3) * 1000;


	Ui::qDebugMatrix4d(robot_tool0_matrix, "robot_tool0_matrix:");

#endif // ER100

	m_context->Deactivate();

}

void OccView::loadDisplayRobotJoints()
{



	STEPControl_Reader reader;
	static int index = 0;
	IFSelect_ReturnStatus stat = reader.ReadFile(robotPath.toUtf8());
	if (stat != IFSelect_RetDone)
		return;
	//加载文件
	Standard_Integer NbRoots = reader.NbRootsForTransfer();
	Standard_Integer num = reader.TransferRoots();
	auto shape = reader.OneShape();
	RobotAISShape[index] = new AIS_Shape(shape);
	m_context->Display(RobotAISShape[index], Standard_True);

	/*index++;
	if (index == 7) {

		RobotAISShape[5]->AddChild(RobotAISShape[6]);
		RobotAISShape[4]->AddChild(RobotAISShape[5]);
		RobotAISShape[3]->AddChild(RobotAISShape[4]);
		RobotAISShape[2]->AddChild(RobotAISShape[3]);
		RobotAISShape[1]->AddChild(RobotAISShape[2]);
		RobotAISShape[0]->AddChild(RobotAISShape[1]);

		index = 0;
	}*/


}

void OccView::loadDisplayWorkpiece()
{
	STEPControl_Reader reader;
	IFSelect_ReturnStatus stat = reader.ReadFile(workpiecePath.toUtf8());
	switch (stat)
	{
	case IFSelect_RetVoid:
		std::cout << "normal execution which created nothing, or no data to process!" << std::endl;
		break;
	case IFSelect_RetDone:
		break;
	case IFSelect_RetError:
		std::cout << "error in command or input data, no execution!" << std::endl;
		break;
	case IFSelect_RetFail:
		std::cout << "execution was run and has failed!" << std::endl;
		break;
	case IFSelect_RetStop:
		std::cout << "indicates end or stop (such as Raise)!" << std::endl;
		break;
	default:
		break;
	}
	if (stat != IFSelect_RetDone)
		return;

	/*******注册progressbar***********/
	OccProgressIndicator* indicat = new OccProgressIndicator();
	QObject::connect(indicat, SIGNAL(updateProgress(int)), this, SLOT(importValue(int)));
	Handle_XSControl_WorkSession ws = reader.WS();
	ws->MapReader()->SetProgress(indicat);
	Standard_Integer NbRoots = reader.NbRootsForTransfer();
	Standard_Integer num = reader.TransferRoots();




	//Mapping STEP entities to Open CASCADE Technology shapes
	PartTopoShape = reader.OneShape();
	auto number = reader.NbShapes();
	qDebug() << "NbRoots:" << NbRoots;
	qDebug() << "num:" << num;
	qDebug() << "number:" << number;

	//qDebug() << "position:" << PartTopoShape.Location().Transformation().TranslationPart().X() << "," << PartTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();
	//gp_Vec vec(200, 200, 700);
	//gp_Trsf rsf01;
	//rsf01.SetTranslationPart(vec);
	//TopLoc_Location loc(rsf01);
	//PartTopoShape.Move(loc);
	//qDebug() << "position01:" << PartTopoShape.Location().Transformation().TranslationPart().X() << "," << PartTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();

	PartAISShape = new AIS_Shape(PartTopoShape);
	if (m_context->HasLocation(PartAISShape)) {
		qDebug() << "m_context->HasLocation(PartAISShape)";
		double rx{ 0.0 }, ry{ 0.0 }, rz{ 0.0 };
		PartTopoShape.Location().Transformation().GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, rx, ry, rz);
		qDebug() << "rx:" << rx << "," << "ry:" << ry << "rz:" << rz;

	}

	double rx{ 0.0 }, ry{ 0.0 }, rz{ 0.0 };
	PartTopoShape.Location().Transformation().GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, rx, ry, rz);
	qDebug() << "rx:" << rx << "," << "ry:" << ry << "rz:" << rz;

	PartAISShape->SetDisplayMode(AIS_Shaded);
	PartAISShape->SetColor(Quantity_NOC_RED);
	m_context->Display(PartAISShape, true);
	m_view->FitAll();

}

void OccView::loadDisplayTool()
{
	STEPControl_Reader reader;
	IFSelect_ReturnStatus stat = reader.ReadFile(toolPath.toUtf8());
	switch (stat)
	{
	case IFSelect_RetVoid:
		std::cout << "normal execution which created nothing, or no data to process!" << std::endl;
		break;
	case IFSelect_RetDone:
		break;
	case IFSelect_RetError:
		std::cout << "error in command or input data, no execution!" << std::endl;
		break;
	case IFSelect_RetFail:
		std::cout << "execution was run and has failed!" << std::endl;
		break;
	case IFSelect_RetStop:
		std::cout << "indicates end or stop (such as Raise)!" << std::endl;
		break;
	default:
		break;
	}
	if (stat != IFSelect_RetDone)
		return;

	//Selecting STEP entities for translation : The whole file
	//加载文件

	/*******注册progressbar***********/
	OccProgressIndicator* indicat = new OccProgressIndicator();
	QObject::connect(indicat, SIGNAL(updateProgress(int)), this, SLOT(importValue(int)));
	Handle_XSControl_WorkSession ws = reader.WS();
	ws->MapReader()->SetProgress(indicat);

	Standard_Integer NbRoots = reader.NbRootsForTransfer();
	Standard_Integer num = reader.TransferRoots();

	//Mapping STEP entities to Open CASCADE Technology shapes
	ToolTopoShape = reader.OneShape();

	auto number = reader.NbShapes();
	qDebug() << "NbRoots:" << NbRoots;
	qDebug() << "num:" << num;
	qDebug() << "number:" << number;

	qDebug() << "position:" << ToolTopoShape.Location().Transformation().TranslationPart().X() << "," << ToolTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();
	qDebug() << "position01:" << ToolTopoShape.Location().Transformation().TranslationPart().X() << "," << ToolTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();




	ToolAISShape = new AIS_Shape(ToolTopoShape);
	if (m_context->HasLocation(ToolAISShape)) {
		qDebug() << "m_context->HasLocation(ToolTopoShape)";
	}

	ToolAISShape->SetDisplayMode(AIS_Shaded);
	ToolAISShape->SetColor(Quantity_NOC_BLUE1);
	m_context->Display(ToolAISShape, true);
	m_view->FitAll();


	gp_Trsf trans, rot, transs;
	trans.SetTranslationPart(gp_Vec(100, 100, 100));
	gp_Quaternion qua;
	qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, 0.0, 0.0, 0.0);
	rot.SetRotation(qua);
	transs = trans * rot;

	//m_context->SetLocation(ToolAISShape, transs);

	auto loc = m_context->Location(ToolAISShape);

	qDebug() << "position:" << ToolTopoShape.Location().Transformation().TranslationPart().X() << "," << ToolTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();
	qDebug() << "position01:" << ToolTopoShape.Location().Transformation().TranslationPart().X() << "," << ToolTopoShape.Location().Transformation().TranslationPart().Y() << "," << PartTopoShape.Location().Transformation().TranslationPart().Z();

	qDebug() << " loc.Transformation().TranslationPart():" << loc.Transformation().TranslationPart().X() << "," << loc.Transformation().TranslationPart().Y() << "," << loc.Transformation().TranslationPart().Z();
	double RX, RY, RZ;
	loc.Transformation().GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, RX, RY, RZ);

	qDebug() << "loc.Transformation().TranslationPart():" << RX << "," << RY << "," << RZ;

	m_context->Update(ToolAISShape, true);
}

void OccView::loadDisplaySTL()
{
	//    StlAPI_Reader aReader_Stl;
	//    TopoDS_Shape shape_Stl;
	//    auto res= aReader_Stl.Read(shape_Stl, stlPath.toUtf8());
	//    if(res){
	//        Handle(AIS_Shape) STLAIS=new AIS_Shape(shape_Stl);
	//        m_context->Display(STLAIS,Standard_True);
	//    }

	RWStl reader_stl;
	Handle(Poly_Triangulation) triFace = reader_stl.ReadFile(stlPath.toUtf8());
	Standard_Integer nTriangles = triFace->NbTriangles();
	TColgp_Array1OfPnt nodes(1, triFace->NbNodes());
	Poly_Array1OfTriangle triangles(1, triFace->NbTriangles());
	nodes = triFace->Nodes();
	triangles = triFace->Triangles();



	//    Handle(AIS_Triangulation) stlais=new AIS_Triangulation(triFace);
	//    //Handle(TColStd_HArray1OfInteger) color=new TColStd_HArray1OfInteger(10);
	//    Handle(TColStd_HArray1OfInteger) anArr = new TColStd_HArray1OfInteger (1, 3);
	//    anArr->SetValue (1,10);
	//    anArr->SetValue (2, 11);
	//    anArr->SetValue (3, 12);
	//    stlais->SetColors(anArr);
	//    m_context->Display(stlais,Standard_True);

	TopoDS_Compound aComp;
	BRep_Builder BuildTool;
	BuildTool.MakeCompound(aComp);

	/*********点呈现**************/
	{
		//        for(Standard_Integer i=nodes.Lower();i<nodes.Upper();i++){
		//            auto point=nodes.Value(i);
		//            TopoDS_Vertex vet=BRepBuilderAPI_MakeVertex(point);

		//            BuildTool.Add( aComp, vet );
		//            qDebug()<<"i:"<<i;

		//        }
		//        Handle(AIS_Shape) ais=new AIS_Shape(aComp);
		//        m_context->Display(ais,Standard_True);
	}


	/*********面片呈现**************/
	{
		//        for(Standard_Integer i=triangles.Lower();i<triangles.Upper();i++){
		//            auto aTriangle=triangles.Value(i);


		//            Standard_Integer nVertexIndex1,nVertexIndex2,nVertexIndex3;
		//            aTriangle.Get(nVertexIndex1, nVertexIndex2, nVertexIndex3);
		//            gp_Pnt  vertex1,vertex2,vertex3;
		//            vertex1 = nodes.Value(nVertexIndex1);
		//            vertex2 = nodes.Value(nVertexIndex2);
		//            vertex3 = nodes.Value(nVertexIndex3);

		//             auto vet=BRepBuilderAPI_MakePolygon(vertex1,vertex2,vertex3);
		//            BuildTool.Add(aComp,vet);
		//            qDebug()<<"i:"<<i;

		//        }
		//        Handle(AIS_Shape) ais=new AIS_Shape(aComp);
		//        m_context->Display(ais,Standard_True);
	}


	qDebug() << "nTriangles:" << nTriangles << "," << triangles.Length();

}

void OccView::displayNormalVector()
{
	//遍历零件的面
	for (TopExp_Explorer e(selectFaceShape, TopAbs_FACE); e.More(); e.Next())
	{
		TopoDS_Face aFace = TopoDS::Face(e.Current());
		//拓扑面和几何曲面的方向相反时反转
		if (aFace.Orientation() == TopAbs_REVERSED)
		{
			aFace.Reversed();
		}
		BRepGProp_Face analysisFace(aFace);
		Standard_Real umin, umax, vmin, vmax;
		analysisFace.Bounds(umin, umax, vmin, vmax);//获取拓扑面的参数范围
		Standard_Real midU, midV;
		midU = (umin + umax) / 2;//拓扑面的参数中点
		midV = (vmin + vmax) / 2;
		gp_Vec norm;
		gp_Pnt midPoint;
		analysisFace.Normal(midU, midV, midPoint, norm);//返回面参数中点的坐标及其法向
		//绘制法线
		gp_Lin normLine(midPoint, gp_Dir(norm));
		TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(normLine, 0, 20);
		NormalVector.push_back(new AIS_Shape(anEdge));
		m_context->Display(NormalVector.back(), Standard_True);
		//Handle(AIS_Shape) ais_shape = new AIS_Shape(anEdge);
		//m_context->Display(ais_shape, Standard_True);
	}
}

void OccView::removeNormalVector()
{
	if (NormalVector.back()) {
		m_context->Remove(NormalVector.back(), Standard_True);
	}
	else {
		qDebug() << "no vector";
	}
}

void OccView::InitView()
{
	if (m_context.IsNull())
	{
		//此对象提供与X server的连接，在Windows和Mac OS中不起作用
		Handle(Aspect_DisplayConnection) m_display_donnection = new Aspect_DisplayConnection();
		//创建OpenGl图形驱动
		if (m_graphic_driver.IsNull())
		{
			m_graphic_driver = new OpenGl_GraphicDriver(m_display_donnection);
		}
		//获取QWidget的窗口系统标识符
		WId window_handle = (WId)winId();
		//创建Windows NT 窗口
		Handle(WNT_Window) wind = new WNT_Window((Aspect_Handle)window_handle);
		//创建3D查看器
		m_viewer = new V3d_Viewer(m_graphic_driver, Standard_ExtString("viewer3d"));
		//创建视图
		m_view = m_viewer->CreateView();
		m_view->SetWindow(wind);
		//打开窗口
		if (!wind->IsMapped())
		{
			wind->Map();
		}
		m_context = new AIS_InteractiveContext(m_viewer);  //创建交互式上下文
		//配置查看器的光照
		m_viewer->SetDefaultLights();
		m_viewer->SetLightOn();
		//设置视图的背景颜色为灰色
		m_view->SetBackgroundColor(Quantity_NOC_GRAY60);
		m_view->MustBeResized();
		//显示直角坐标系，可以配置在窗口显示位置、文字颜色、大小、样式
		// m_view->TriedronDisplay(Aspect_TOTP_CENTER, Quantity_NOC_GOLD, 0.08, V3d_WIREFRAME);
		//设置显示模式
		m_context->SetDisplayMode(AIS_Shaded, Standard_True);



		opencascade::handle<AIS_ViewCube> aisViewCube = new AIS_ViewCube;
		aisViewCube->SetBoxColor(Quantity_NOC_GRAY75);
		aisViewCube->SetFixedAnimationLoop(false);
		aisViewCube->SetSize(55);
		aisViewCube->SetFontHeight(12);
		aisViewCube->SetAxesLabels("", "", "");
		aisViewCube->SetTransformPersistence(
			new Graphic3d_TransformPers(
				Graphic3d_TMF_TriedronPers,
				Aspect_TOTP_LEFT_LOWER,
				Graphic3d_Vec2i(85, 85)));

		aisViewCube->Attributes()->DatumAspect()->LineAspect(Prs3d_DP_XAxis)->SetColor(Quantity_NOC_RED2);
		const Handle_Prs3d_DatumAspect& datumAspect = aisViewCube->Attributes()->DatumAspect();
		datumAspect->ShadingAspect(Prs3d_DP_XAxis)->SetColor(Quantity_NOC_RED2);
		datumAspect->ShadingAspect(Prs3d_DP_YAxis)->SetColor(Quantity_NOC_GREEN2);
		datumAspect->ShadingAspect(Prs3d_DP_ZAxis)->SetColor(Quantity_NOC_BLUE2);
		m_context->Display(aisViewCube, true);



		//获取原始坐标系
		Handle_Geom_Axis2Placement axis = new Geom_Axis2Placement(gp::XOY());
		Handle_AIS_Trihedron aisTrihedron = new AIS_Trihedron(axis);
		aisTrihedron->SetDatumDisplayMode(Prs3d_DM_WireFrame);
		aisTrihedron->SetDrawArrows(false);
		aisTrihedron->Attributes()->DatumAspect()->LineAspect(Prs3d_DP_XAxis)->SetWidth(2.5);
		aisTrihedron->Attributes()->DatumAspect()->LineAspect(Prs3d_DP_YAxis)->SetWidth(2.5);
		aisTrihedron->Attributes()->DatumAspect()->LineAspect(Prs3d_DP_ZAxis)->SetWidth(2.5);
		aisTrihedron->SetDatumPartColor(Prs3d_DP_XAxis, Quantity_NOC_RED2);
		aisTrihedron->SetDatumPartColor(Prs3d_DP_YAxis, Quantity_NOC_GREEN2);
		aisTrihedron->SetDatumPartColor(Prs3d_DP_ZAxis, Quantity_NOC_BLUE2);
		aisTrihedron->SetLabel(Prs3d_DP_XAxis, "X");
		aisTrihedron->SetLabel(Prs3d_DP_YAxis, "Y");
		aisTrihedron->SetLabel(Prs3d_DP_ZAxis, "Z");
		aisTrihedron->SetTextColor(Quantity_NOC_GRAY40);
		aisTrihedron->SetSize(60);
		aisTrihedron->SetTransformPersistence(
			new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, axis->Ax2().Location()));
		aisTrihedron->Attributes()->SetZLayer(Graphic3d_ZLayerId_Topmost);
		aisTrihedron->SetInfiniteState(true);
		m_context->Display(aisTrihedron, true);

		//        for (TopExp_Explorer exp (theBox,TopAbs_FACE);exp.More();exp.Next()) {
		//            TopoDS_Face aCurrentFace = TopoDS::Face(exp.Current());
		//            //测试当前面的方向
		//            TopAbs_Orientation orient = aCurrentFace.Orientation();
		//            //重新生成几何平面
		//            TopLoc_Location location;
		//            Handle (Geom_Surface) aGeometricSurface = BRep_Tool::Surface(aCurrentFace,location);
		//            Handle (Geom_Plane) aPlane = Handle (Geom_Plane)::DownCast(aGeometricSurface);
		//            Handle(AIS_Shape) Blue01 =new AIS_Shape(aPlane);
		//            m_context->Display(aPlane,Standard_True);
		//            //Build an AIS_Shape with a new color
		//            //创建一个新的AIS_Shape
		//            Handle(AIS_Shape) theMovingFace = new AIS_Shape(aCurrentFace);
		//            Quantity_NameOfColor aCurrentColor = (Quantity_NameOfColor)j;
		//            m_context->SetColor(theMovingFace,aCurrentColor,Standard_False);
		//            m_context->SetMaterial(theMovingFace,Graphic3d_NOM_PLASTIC,Standard_False);

		//            //查找每个面的法向量
		//            gp_Pln agpPlane = aPlane->Pln();



		//            gp_Ax1 norm = agpPlane.Axis();
		//            gp_Dir dir = norm.Direction();
		//            gp_Vec move(dir);
		//            TopLoc_Location aLocation;
		//            Handle (AIS_ConnectedInteractive) theTransformedDisplay = new AIS_ConnectedInteractive();
		//            theTransformedDisplay->Connect(theMovingFace, aLocation);
		//            // = myAISContext->Location(theMovingFace);
		//            Handle (Geom_Transformation) theMove = new Geom_Transformation(aLocation.Transformation());
		//            for (Standard_Integer i=1;i<=30;i++) {
		//                theMove->SetTranslation(move*i);
		//                if (orient==TopAbs_FORWARD) m_context->SetLocation(theTransformedDisplay,TopLoc_Location(theMove->Trsf()));
		//               else m_context->SetLocation(theTransformedDisplay,TopLoc_Location(theMove->Inverted()->Trsf()));
		//                m_context->Redisplay(theTransformedDisplay,Standard_False);
		//            }

		//            j+=15;
		//        }


		//        TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(gp_Pnt(-200.,-200.,0.));

		//        gp_Trsf theTransformation;
		//        gp_Ax1 axe(gp_Pnt(110, 60, 60),  gp_Dir(0.0, 1.0, 0.0));
		//        theTransformation.SetMirror(axe);
		//        BRepBuilderAPI_Transform myBRepTransformation(V1,theTransformation,false);
		//        TopoDS_Shape S2 = myBRepTransformation.Shape();
		//        Handle(AIS_Shape) ddd=new AIS_Shape(V1);
		//        m_context->Display(ddd,true);
		//        Handle(AIS_Shape) ddd01=new AIS_Shape(S2);
		//        m_context->Display(ddd01,true);

		//        TopoDS_Edge E11 = BRepBuilderAPI_MakeEdge(gp_Pnt(40.,0.,0.), gp_Pnt(82.5,25.,0.));
		//        TopoDS_Edge E15 = BRepBuilderAPI_MakeEdge(gp_Pnt(82.5,25.,0.), gp_Pnt(42.5,93.,0.));
		//        TopoDS_Edge E12 = BRepBuilderAPI_MakeEdge(gp_Pnt(82.5,25.,0.), gp_Pnt(42.5,93.,0.));
		//        TopoDS_Edge E13 = BRepBuilderAPI_MakeEdge(gp_Pnt(42.5,93.,0.), gp_Pnt(0.,68.,0.));
		//        TopoDS_Edge E14 = BRepBuilderAPI_MakeEdge(gp_Pnt(0.,68.,0.), gp_Pnt(40.,0.,0.));
		//        TopoDS_Wire W1 = BRepBuilderAPI_MakeWire(E11,E12,E13,E14);
		//        Handle(AIS_Shape) ddd02=new AIS_Shape(W1);
		//        m_context->Display(ddd02,Standard_True);


		//        gp_Pln aPlane;

		//        gp_Circ aCircle1(gp::XOY(), 1.0);
		//        gp_Circ aCircle2(gp::XOY(), 1.0);
		//        gp_Circ aCircle3(gp::XOY(), 1.0);

		//        Handle(AIS_Shape) ddd03=new AIS_Shape(BRepBuilderAPI_MakeEdge(aCircle3));

		//        aCircle1.SetLocation(gp_Pnt(3.0, 3.0, 0.0));
		//        aCircle2.SetLocation(gp_Pnt(7.0, 3.0, 0.0));
		//        aCircle3.SetLocation(gp_Pnt(3.0, 7.0, 0.0));

		//        BRepBuilderAPI_MakeEdge anEdgeMaker1(aCircle1);
		//        BRepBuilderAPI_MakeEdge anEdgeMaker2(aCircle2);
		//        BRepBuilderAPI_MakeEdge anEdgeMaker3(aCircle3);

		//        BRepBuilderAPI_MakeWire aWireMaker1(anEdgeMaker1.Edge());
		//        BRepBuilderAPI_MakeWire aWireMaker2(anEdgeMaker2.Edge());
		//        BRepBuilderAPI_MakeWire aWireMaker3(anEdgeMaker3.Edge());

		//        BRepBuilderAPI_MakeFace aFaceMaker(aPlane, 0.0, 10.0, 0.0, 10.0);

		//        Geom_CartesianPoint p01(gp_Pnt(0,0,0));
		//        Geom_Plane pln1(aPlane);


		//        gp_Ax2 axis00(gp_Pnt(1, 2, 3), gp::DZ());
		//        std::ofstream dumpFile("geometrySurface.txt");
		//        Handle_Geom_Circle baseCurve = new Geom_Circle(axis00, 4.0);
		//        Handle_Geom_SurfaceOfLinearExtrusion theExtrusion = new Geom_SurfaceOfLinearExtrusion(baseCurve, gp_Dir(0, 0.6, 0.8));
		//        //        GeomTools::Write(theExtrusion, dumpFile);
		//        //        GeomTools::Dump(theExtrusion, dumpFile);
		//        //        GeomTools::Write(theExtrusion, std::cout);
		//        //        GeomTools::Dump(theExtrusion, std::cout);

		//        Handle_Geom_CylindricalSurface theCylinder = new Geom_CylindricalSurface(axis00, 4.0);
		//        TopoDS_Shape cylin=BRepPrimAPI_MakeCylinder(3,20,10);
		//        Handle(AIS_Shape) aisCylin=new AIS_Shape(cylin);
		//        m_context->Display(aisCylin,Standard_True);
	}
	//配置QWidget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setBackgroundRole(QPalette::NoRole);  //无背景
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setMouseTracking(true);   //开启鼠标位置追踪
}

void OccView::InitFilters()
{
	aFil1 = new StdSelect_FaceFilter(StdSelect_Revol);
	aFil2 = new StdSelect_FaceFilter(StdSelect_Plane);
}

void OccView::pickUp(TopoDS_Shape)
{
	//提取工件中所有的面
	TopExp_Explorer Ex;
	workpiece_show_faces.clear();
	int index = 0;
	for (Ex.Init(PartTopoShape, TopAbs_FACE); Ex.More(); Ex.Next())
	{
		index++; //按顺序给定面的索引
		TopoDS_Face current_face = TopoDS::Face(Ex.Current());   //将资源管理器里面的面对象转到容器中
		Show_face result;
		result.face = current_face;
		result.adv_face_index = index;
		workpiece_show_faces.push_back(result); //这边就是将result这个结构体放入容器workpiece_show_faces中
	}
}

void OccView::getShape()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		selectFaceShape = abc;
		TopAbs_ShapeEnum bba = abc.ShapeType();
		qDebug() << bba;

		int size = workpiece_show_faces.size();
		for (int i = 0; i < size; i++)
		{
			TopoDS_Shape cur_face = workpiece_show_faces.at(i).face;
			Standard_Boolean abd = cur_face.IsEqual(abc);
			if (abd)
			{
				qDebug() << workpiece_show_faces.at(i).adv_face_index;
			}
		}
	}
}

void OccView::selectMode(Handle(AIS_Shape) selectmode, const Ui::selectionType& type)
{
	//shading visualization mode, no specific mode, authorization for decomposition into sub-shapes
	//着色可视化模式，无特定模式，授权分解为子形状
	//const TopoDS_Shape theShape;
	//Handle(AIS_Shape) aShapePrs = new AIS_Shape(theShape);
	//m_context->Display(aShapePrs, AIS_Shaded, -1, true, true);
	//m_context->Display(selectmode, AIS_Shaded, -1, true, true);
	//activates decomposition of shapes into faces
	//激活将形状分解为面
	//auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_VERTEX);
	//m_context->Activate(aShapePrs, aSubShapeSelMode);
	//m_context->Activate(selectmode, aSubShapeSelMode);
	//m_context->AddFilter(aFil1);
	//m_context->AddFilter(aFil2);
	//only faces of revolution or planar faces will be selected
	//仅选择旋转面或平面
	//m_context->MoveTo(thePixelX, thePixelY, myView, true);

	//m_context->RemoveFilter(aFil1);
	//m_context->RemoveFilter(aFil2);

	m_context->Display(selectmode, AIS_Shaded, -1, true, true);

	if (type == Ui::selectionType::FaceSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_FACE);
		m_context->Activate(selectmode, aSubShapeSelMode);
	}
	else if (type == Ui::selectionType::VetextSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_VERTEX);
		m_context->Activate(selectmode, aSubShapeSelMode);
	}
	else if (type == Ui::selectionType::EdgeSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_EDGE);
		m_context->Activate(selectmode, aSubShapeSelMode);
	}
}

void OccView::DisselectMode(Handle(AIS_Shape) selectmode, const Ui::selectionType& type) {
	if (type == Ui::selectionType::FaceSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_FACE);
		m_context->Deactivate(selectmode, aSubShapeSelMode);
	}
	else if (type == Ui::selectionType::VetextSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_VERTEX);
		m_context->Deactivate(selectmode, aSubShapeSelMode);
	}
	else if (type == Ui::selectionType::EdgeSel) {
		auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_EDGE);
		m_context->Deactivate(selectmode, aSubShapeSelMode);
	}

}

void OccView::newPartCoordinate()
{
	//    gp_Pnt oPnt(0, 0, 0);//原点

	//    gp_Pnt xPnt(1, 1, 1);
	//    gp_Vec vX(oPnt, xPnt);
	//    gp_Dir aixX(vX / vX.Magnitude());//x方向

	//    gp_Vec constructV= vX.Rotated(gp_Ax1(oPnt,gp_Dir(0,0,1)),1.571);	//对X轴进行旋转构造一个向量叉乘计算Z轴
	//    gp_Vec vZ = vX.Crossed(constructV);
	//    gp_Dir aixZ = (vZ / vZ.Magnitude());//z方向

	//    gp_Ax2 ax = gp_Ax2(oPnt, aixZ, aixX);
	//    Handle(Geom_Axis2Placement) TrihedronAxis = new Geom_Axis2Placement(ax);
	//    Handle(AIS_Trihedron) partTrihedron = new AIS_Trihedron(TrihedronAxis);
	//    m_context->Display(partTrihedron, Standard_True);

	//    gp_Ax3 ay0(ax);
	//    ay0.XReverse();

	//    ay0.Ax2();


	if (firstPointSelected && secondPointSelected && thirdPointSelected) {
		firstPointSelected = secondPointSelected = thirdPointSelected = false;
	}

	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_VERTEX) {
			if (!firstPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointO = BRep_Tool::Pnt(V);
				firstPointSelected = true;
				qDebug() << pointO.X() << "," << pointO.Y() << "," << pointO.Z();
				gp_Pnt gPnt(100.0, 100.0, 100.0);


			}
			else if (firstPointSelected && !secondPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointX = BRep_Tool::Pnt(V);
				secondPointSelected = true;
				qDebug() << pointX.X() << "," << pointX.Y() << "," << pointX.Z();
			}
			else  if (firstPointSelected && secondPointSelected && !thirdPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointY = BRep_Tool::Pnt(V);
				thirdPointSelected = true;
				qDebug() << pointY.X() << "," << pointY.Y() << "," << pointY.Z();
				gp_Vec vX(pointO, pointX);
				gp_Dir aixX(vX / vX.Magnitude());//x方向

				gp_Vec vY(pointO, pointY);
				gp_Dir aixY(vY / vY.Magnitude());//y方向

				gp_Vec vZ = vX.Crossed(vY);

				gp_Dir aixZ = (vZ / vZ.Magnitude());//z方向

				part0Ax2 = gp_Ax2(pointO, aixZ, aixX);
				PartTrihedronAxis = new Geom_Axis2Placement(part0Ax2);
				partTrihedron = new AIS_Trihedron(PartTrihedronAxis);

				m_context->Display(partTrihedron, Standard_True);
				partTrihedron->AddChild(PartAISShape);
				RobotAISShape[6]->AddChild(partTrihedron);


				gp_Ax3 origin(gp::XOY());
				gp_Ax3 current(part0Ax2);
				gp_Trsf tran;
				tran.SetTransformation(current, origin);
				auto posTran = tran.TranslationPart();
				qDebug() << "NewCoordinatePostion:" << posTran.X() << "," << posTran.Y() << "," << posTran.Z();
				double Rx, Ry, Rz;
				tran.GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, Rx, Ry, Rz);
				qDebug() << "NewCoordinateVelity:" << Rx << "," << Ry << "," << Rz;

				getPartCoor().x = originPart0Coordinate.x = posTran.X(); getPartCoor().y = originPart0Coordinate.y = posTran.Y(); getPartCoor().z = originPart0Coordinate.z = posTran.Z();
				getPartCoor().rx = originPart0Coordinate.rx = Rx; getPartCoor().ry = originPart0Coordinate.ry = Ry; getPartCoor().rz = originPart0Coordinate.rz = Rz;

				emit NewPartCoordinateCompleteSigal();

			}
		}
	}

	gp_GTrsf trsf01;


	//    Handle(Geom_Axis2Placement) TrihedronAxisL = new Geom_Axis2Placement(ax);
	//    gp_Dir yDirection = TrihedronAxisL->YDirection();
	//    gp_Pnt location = TrihedronAxisL->Ax2().Location();
	//    gp_Ax1 retation_axiY(location, yDirection);
	//    gp_Trsf rotation_trans;
	//    rotation_trans.SetRotation(retation_axiY, deg);
	//    TrihedronAxisL->Transform(rotation_trans);
	//    Handle(AIS_Trihedron) partTrihedron = new AIS_Trihedron(TrihedronAxisL);
	//    m_context->Display(partTrihedron, Standard_True);
	//    m_view->FitAll();
	//    return;

}

void OccView::newToolCoordinate()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_VERTEX) {
			if (!firstPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointO = BRep_Tool::Pnt(V);
				firstPointSelected = true;
				qDebug() << "pointO:" << pointO.X() << "," << pointO.Y() << "," << pointO.Z();
				gp_Pnt gPnt(100.0, 100.0, 100.0);

				/*Standard_CString str = "first point:";
				TCollection_ExtendedString extStr(str);

				Handle(AIS_TextLabel) aPntLabel = new AIS_TextLabel();
				aPntLabel->SetText(extStr);
				aPntLabel->SetPosition(gPnt);
				aPntLabel->SetFont("Microsoft yahei");
				m_context->Display(aPntLabel, Standard_True);*/

			}
			else if (firstPointSelected && !secondPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointX = BRep_Tool::Pnt(V);
				secondPointSelected = true;
				qDebug() << pointX.X() << "," << pointX.Y() << "," << pointX.Z();
			}
			else  if (firstPointSelected && secondPointSelected && !thirdPointSelected) {
				TopoDS_Vertex V = TopoDS::Vertex(abc);
				pointY = BRep_Tool::Pnt(V);
				thirdPointSelected = true;
				qDebug() << pointY.X() << "," << pointY.Y() << "," << pointY.Z();
				gp_Vec vX(pointO, pointX);
				gp_Dir aixX(vX / vX.Magnitude());//x方向

				gp_Vec vY(pointO, pointY);
				gp_Dir aixY(vY / vY.Magnitude());//y方向

				//gp_Vec constructV = vX.Rotated(gp_Ax1(pointO, vY), -1.571);	//对X轴进行旋转构造一个向量叉乘计算Z轴
				gp_Vec vZ = vX.Crossed(vY);

				//gp_Dir aixZ = (vZ / vZ.Magnitude());//z方向
				gp_Dir aixZ = (vZ / vZ.Magnitude());//z方向

				part0Ax2 = gp_Ax2(pointO, aixZ, aixX);

				ToolTrihedronAxis = new Geom_Axis2Placement(part0Ax2);

				toolTrihedron = new AIS_Trihedron(ToolTrihedronAxis);

				gp_Vec vY_new = vZ.Crossed(vX);
				gp_Dir aixY_new = vY_new / vY_new.Magnitude();

				/*		Eigen::AngleAxisd rotation_vector(alpha, Eigen::Vector3d(x, y, z));
						Eigen::Vector3d ttt();*/


				m_context->Display(toolTrihedron, Standard_True);
				toolTrihedron->AddChild(ToolAISShape);
				Handle(Geom_Axis2Placement) originAxis = new Geom_Axis2Placement(gp::XOY());
				Handle(AIS_Trihedron) originTrihedron = new AIS_Trihedron(originAxis);
				originTrihedron->SetDatumPartColor(Prs3d_DP_XAxis, Quantity_NOC_RED2);
				originTrihedron->SetDatumPartColor(Prs3d_DP_YAxis, Quantity_NOC_GREEN2);
				originTrihedron->SetDatumPartColor(Prs3d_DP_ZAxis, Quantity_NOC_BLUE2);
				m_context->Display(originTrihedron, Standard_True);
				toolTrihedron->AddChild(originTrihedron);




				gp_Ax3 origin(gp::XOY());
				gp_Ax3 current(part0Ax2);

				gp_Trsf toolTrihedronOriginTran;

				toolTrihedronOriginTran.SetTransformation(current, origin);


				auto transPM = Ui::transf2Matrix_02(toolTrihedronOriginTran);

				double pe[6]{ 0.0 };
				/*	pe[0] = pointO.X();   pe[1] = pointO.Y();   pe[2] = pointO.Z();
					if (aixZ.X() != 1) {
						pe[4] = asin(aixZ.X());
						pe[3] = -asin(aixZ.Y() / cos(pe[4]));
						pe[5] = asin(aixX.Y()*cos(pe[3]) + aixX.Z()*sin(pe[3]));
					}
					else {
						pe[4] = PI / 2;
						pe[3] = PI / 2;
						pe[5] = 0.0;
					}*/

				Ui::s_pm2pe(transPM, pe, "123");

				qDebug() << "result::::";
				qDebug() << pe[0];
				qDebug() << pe[1];
				qDebug() << pe[2];
				qDebug() << pe[3] * 180 / PI;
				qDebug() << pe[4] * 180 / PI;
				qDebug() << pe[5] * 180 / PI;

				qDebug() << "aixX:" << aixX.X() << "," << aixX.Y() << "," << aixX.Z();
				qDebug() << "aixY_new:" << aixY_new.X() << "," << aixY_new.Y() << "," << aixY_new.Z();
				qDebug() << "aixZ:" << aixZ.X() << "," << aixZ.Y() << "," << aixZ.Z();

				getToolCoor().x = originTool0Coordinate.x = pe[0];    getToolCoor().y = originTool0Coordinate.y = pe[1];    getToolCoor().z = originTool0Coordinate.z = pe[2];
				getToolCoor().rx = originTool0Coordinate.rx = pe[3];  getToolCoor().ry = originTool0Coordinate.ry = pe[4];  getToolCoor().rz = originTool0Coordinate.rz = pe[5];

				//Eigen::Quaterniond quaternion(1, 2, 3, 4);
				//Eigen::Matrix4d matrixxx;
				// 		

				//auto posTran = toolTrihedronOriginTran.TranslationPart();
				//qDebug() << "NewCoordinatePostion:" << posTran.X() << "," << posTran.Y() << "," << posTran.Z();
				//double Rx, Ry, Rz;
				//toolTrihedronOriginTran.GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, Rx, Ry, Rz);
				//qDebug() << "NewCoordinateVelity:" << Rx << "," << Ry << "," << Rz;

				////getToolCoor().x = originTool0Coordinate.x = posTran.X(); getToolCoor().y = originTool0Coordinate.y = posTran.Y(); getToolCoor().z = originTool0Coordinate.z = posTran.Z();
				////getToolCoor().rx = originTool0Coordinate.rx = Rx; getToolCoor().ry = originTool0Coordinate.ry = Ry; getToolCoor().rz = originTool0Coordinate.rz = Rz;


				//auto loc = m_context->Location(toolTrihedron);

				//loc.Transformation().GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, Rx, Ry, Rz);
				//qDebug() << loc.Transformation().TranslationPart().X() << loc.Transformation().TranslationPart().Y() << loc.Transformation().TranslationPart().Z();
				//qDebug() << Rx; qDebug() << Ry; qDebug() << Rz;

				m_context->Update(toolTrihedron, true);
				m_context->Update(originTrihedron, true);

				emit NewToolCoordinateCompleteSigal();

			}
		}
	}
}

void OccView::startSelectFirstCurve()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
			auto V = TopoDS::Edge(abc);
			PairfirstCurve = { "FIRSTCURVE",V };
			selectFirstCurve = false;
			emit firstCurveCompleteSigal();
		}
	}
}

void OccView::startSelectSecondCurve()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
			auto V = TopoDS::Edge(abc);


			PairsecondCurve = { "SECONDCURVE",V };
			emit secondCurveCompleteSigal();
		}
	}
}

void OccView::startSelectPlains()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE) {
			auto V = TopoDS::Face(abc);

			selectFaces = false;
			PairPlains.push_back({ "faces",V });

			emit faceSelectCompleteSigal();
		}
	}
}

void OccView::coutPointCoor()
{
	if (m_context->HasDetectedShape()) {
		TopoDS_Shape abc = m_context->DetectedShape();
		if (abc.ShapeType() == TopAbs_ShapeEnum::TopAbs_VERTEX) {
			TopoDS_Vertex V = TopoDS::Vertex(abc);
			pointO = BRep_Tool::Pnt(V);
			qDebug() << "PointCoordinate:" << pointO.X() << "," << pointO.Y() << "," << pointO.Z();
		}
	}
}

void OCAFBrowser::load(QTreeWidget* theTree)
{
	theTree->clear();

	QTreeWidgetItem* root = new QTreeWidgetItem();
	root->setText(0, QLatin1String("0"));
	root->setIcon(0, myGroupIcon);
	theTree->addTopLevelItem(root);
	load(pDoc->GetData()->Root(), root, QString::fromLatin1("0"));

	//    {
	//        TDF_Label mainLabel = pDoc->Main();
	//        Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
	//        Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
	//        TDF_LabelSequence tdfLabels;
	//        ShapeTool->GetFreeShapes(tdfLabels);   //获取装配体和组件对应名称
	//        int Roots = tdfLabels.Length();
	//        TDF_Label Label = tdfLabels.Value(1);
	//        TDF_LabelSequence components;
	//        ShapeTool->GetComponents(Label, components);
	//        qDebug()<<"components:"<<components.Length();
	//        for (Standard_Integer compIndex = 1; compIndex <= components.Length(); ++compIndex)
	//        {
	//            TDF_Label ChildLabel = components.Value(compIndex);
	//            Handle(TDataStd_Name) name;
	//            if (ChildLabel.FindAttribute(TDataStd_Name::GetID(), name)) {
	//                QTreeWidgetItem *item=new QTreeWidgetItem();
	//                QString text = QString::fromLatin1("%1").arg(QString::fromUtf8(toString(name->Get()).c_str()));
	//                item->setText(0, text);
	//                root->addChild(item);
	//            }

	//        }

	//        TDF_Label Label00 = components.Value(2);

	//        Handle(XCAFDoc_ShapeTool) ShapeTool00 = XCAFDoc_DocumentTool::ShapeTool(mainLabel);

	//        auto shape=ShapeTool00->GetShape(Label00);
	//        gp_Vec gv(100,200,300);
	//        gp_Trsf tf;
	//        tf.SetTranslationPart(gv);




	//        TopLoc_Location loctf(tf);
	//        shape.Move(loctf);

	//        auto res=ShapeTool00->IsAssembly(Label00);
	//        qDebug()<<"isShape:"<<res;



	//    }
}

void OCAFBrowser::load(const TDF_Label& label, QTreeWidgetItem* item, const QString& s)
{

	Handle(TDataStd_Name) name;
	if (label.FindAttribute(TDataStd_Name::GetID(), name)) {
		QString text = QString::fromLatin1("%1 %2").arg(s).arg(QString::fromUtf8(toString(name->Get()).c_str()));
		item->setText(0, text);
	}

	for (TDF_ListIteratorOfIDList it(myList); it.More(); it.Next()) {
		Handle(TDF_Attribute) attr;
		if (label.FindAttribute(it.Value(), attr)) {
			QTreeWidgetItem* child = new QTreeWidgetItem();
			if (it.Value() == TDataStd_Name::GetID()) {
				QString text;
				QTextStream str(&text);
				str << attr->DynamicType()->Name();
				str << " = " << toString(Handle(TDataStd_Name)::DownCast(attr)->Get()).c_str();
				child->setText(0, text);
				item->addChild(child);
			}
			else if (it.Value() == TDF_TagSource::GetID()) {
				QString text;
				QTextStream str(&text);
				str << attr->DynamicType()->Name();
				str << " = " << Handle(TDF_TagSource)::DownCast(attr)->Get();
				child->setText(0, text);
				item->addChild(child);
			}
			else if (it.Value() == TDataStd_Integer::GetID()) {
				QString text;
				QTextStream str(&text);
				str << attr->DynamicType()->Name();
				str << " = " << Handle(TDataStd_Integer)::DownCast(attr)->Get();
				child->setText(0, text);
				item->addChild(child);
			}
			else if (it.Value() == TNaming_NamedShape::GetID()) {
				TopoDS_Shape shape = Handle(TNaming_NamedShape)::DownCast(attr)->Get();
				QString text;
				QTextStream str(&text);
				str << attr->DynamicType()->Name() << " = ";
				if (!shape.IsNull()) {
					switch (shape.ShapeType()) {
					case TopAbs_COMPOUND:
						str << "COMPOUND PRIMITIVE";
						break;
					case TopAbs_COMPSOLID:
						str << "COMPSOLID PRIMITIVE";
						break;
					case TopAbs_SOLID:
						str << "SOLID PRIMITIVE";
						break;
					case TopAbs_SHELL:
						str << "SHELL PRIMITIVE";
						break;
					case TopAbs_FACE:
						str << "FACE PRIMITIVE";
						break;
					case TopAbs_WIRE:
						str << "WIRE PRIMITIVE";
						break;
					case TopAbs_EDGE:
						str << "EDGE PRIMITIVE";
						break;
					case TopAbs_VERTEX:
						str << "VERTEX PRIMITIVE";
						break;
					case TopAbs_SHAPE:
						str << "SHAPE PRIMITIVE";
						break;
					}
				}
				child->setText(0, text);
				item->addChild(child);
			}
			else {
				child->setText(0, QLatin1String(attr->DynamicType()->Name()));
				item->addChild(child);
			}
		}
	}

	int i = 1;
	for (TDF_ChildIterator it(label); it.More(); it.Next(), i++) {
		QString text = QString::fromLatin1("%1:%2").arg(s).arg(i);
		QTreeWidgetItem* child = new QTreeWidgetItem();
		child->setText(0, text);
		child->setIcon(0, myGroupIcon);
		item->addChild(child);
		load(it.Value(), child, text);
	}
}

gp_Pnt OccView::ChangeCoordinateSecond(double x, double y)
{
	gp_Pnt P0, P1, P3;
	gp_Vec Vp2;
	//Handle(Geom_Curve) aCurve;
	double X, Y, Z, VX, VY, VZ;
	this->getView()->Convert(int(x), int(y), X, Y, Z);
	this->getView()->Proj(VX, VY, VZ);
	P1.SetCoord(X, Y, Z);
	Vp2.SetCoord(VX, VY, VZ);
	gp_Lin gpLin(P1, gp_Dir(Vp2));

	//
	//   auto aCurve=GC_MakeSegment(gpLin,-10000,10000);
	//   //Handle(Geom_Surface) aGeometricSurface;

	//    GeomAPI_IntCS CS (aCurve,aGeometricSurface);   //aGeometricSurface为与直线相交的面

	//    Standard_Integer NbSeg = 0;
	//    Standard_Integer NbPoints = 0;
	//    Handle(Geom_Curve) segment;
	//    if(CS.IsDone())
	//    {
	//        NbSeg = CS.NbSegments();
	//        for (Standard_Integer k=1; k<=NbSeg; k++)
	//        {
	//            segment = CS.Segment(k);
	//        }

	//        NbPoints = CS.NbPoints();
	//        for (int k=1; k<=NbPoints; k++)
	//        {
	//            gp_Pnt aPoint=CS.Point(k);
	//            P3=aPoint;
	//        }
	//    }
	return P3;
}

void OccView::AnaminationStart()
{
	//    qDebug()<<"start";
	//    gp_Trsf endRotation;
	//    gp_Quaternion endaQ;
	//    endaQ.SetEulerAngles(gp_YawPitchRoll,0.12,0,0);
	//    endRotation.SetRotation(endaQ);

	//    //设置平移向量
	//    gp_Trsf endranslation;
	//    gp_Vec theVectorOfTransEnd(10,0,0);
	//    endranslation.SetTranslation(theVectorOfTransEnd);
	//    gp_Trsf endTrsf = endranslation * endRotation;




	//    gp_Trsf startRotation;
	//    gp_Quaternion startaQ;
	//    startaQ.SetEulerAngles(gp_YawPitchRoll,0,0,0);
	//    endRotation.SetRotation(startaQ);

	//    //设置平移向量
	//    gp_Trsf startranslation;
	//    gp_Vec theVectorOfTransStart(0,0,0);
	//    endranslation.SetTranslation(theVectorOfTransStart);
	//    gp_Trsf startTrsf= startranslation * startRotation;


	//    m_context->SetLocation(getAISShape(),endTrsf);
	//    m_context->Update(getAISShape(),Standard_True);


	//    int currentTime=0;
	//    QEasingCurve m_easingCurve;
	//    for (int k=0;k<1000;k++) {
	//        currentTime++;
	//        qDebug()<<currentTime;
	//        double t = m_easingCurve.valueForProgress(currentTime / double(1000));
	//        qDebug()<<t;
	//        const bool prevImmediateUpdate = m_view->SetImmediateUpdate(false);
	//        qDebug()<<"1";
	//        NCollection_Lerp<gp_Vec>  TransLerp;

	//        NCollection_Lerp<gp_Quaternion> RotLerp;

	//        TransLerp.Init(theVectorOfTransStart,theVectorOfTransEnd);
	//        RotLerp.Init(startTrsf.GetRotation(),endTrsf.GetRotation());

	//        gp_Vec nowXYZ;
	//        gp_Quaternion nowRot;
	//        TransLerp.Interpolate(t,nowXYZ);
	//        qDebug()<<"2";
	//        //RotLerp.Interpolate(t,nowRot);
	//        qDebug()<<"3";

	//        gp_Trsf nowTrsf;
	//        nowTrsf.SetTranslation(nowXYZ);
	//        nowTrsf.SetRotation(nowRot);
	//        m_context->SetLocation(getAISShape(),startTrsf);
	//        m_context->Update(getAISShape(),Standard_True);
	//    }


	/*double ddd[6]{ 1,0,0,0,0,0 };
	for (int k = 0; k < 100; k++) {
		qDebug() << ddd[0];
		ddd[0] += 1;
		SetModelLocation_Euler(this->getAISShape(), ddd);
		QThread::msleep(100);
	}



	TopoDS_Shape S;
	gp_Trsf *theTransformation = new gp_Trsf();
	gp_Ax3 *ax3_1 = new gp_Ax3(*new gp_Pnt(0, 0, 0), *new gp_Dir(0, 0, 1));  //左手坐标系
	gp_Ax3 *ax3_2 = new gp_Ax3(*new gp_Pnt(60, 60, 60), *new gp_Dir(1, 1, 1));


	theTransformation->SetDisplacement(*ax3_1, *ax3_2);*/



	//    BRepBuilderAPI_Transform myBRepTransformation =new BRepBuilderAPI_Transform(S, theTransformation, false);
	//    TopoDS_Shape TransformedShape = myBRepTransformation->Shape();


}

// 刷新页面
void OccView::visual_update() {
	//QT计时器：每10ms刷新显示
	m_context->UpdateCurrentViewer();
}

void OccView::SetModelLocation(Handle(AIS_Shape)& aShape, gp_Trsf trsf)
{
	Handle_AIS_InteractiveObject Current(aShape);
	if (!Current.IsNull())
	{

		m_context->SetLocation(Current, trsf);
		m_context->Update(Current, Standard_True);  //等价于这句话 myContext->UpdateCurrentViewer();//窗口更新
	}
}

//设置当前对象的位置
void OccView::SetModelLocation_Matrix(Handle(AIS_Shape)& aShape, double* matrixTemp)
{


	cameraStart = getView()->Camera();
	gp_Trsf trsf;

	//    auto axe = new gp_Ax1(*new gp_Pnt(200, 60, 60), *new gp_Dir(0.0, 1.0, 0.0));//指定旋转轴
	//    trsf.SetTranslation(*new gp_Pnt(200, 60, 60),*new gp_Pnt(201, 60, 60));
	trsf.SetValues(matrixTemp[0], matrixTemp[1], matrixTemp[2], matrixTemp[3],
		matrixTemp[4], matrixTemp[5], matrixTemp[6], matrixTemp[7],
		matrixTemp[8], matrixTemp[9], matrixTemp[10], matrixTemp[11]);
	qDebug() << "1";
	SetModelLocation(aShape, trsf);
}

//通过YPR角度设置当前对象的位置
void OccView::SetModelLocation_Euler(Handle(AIS_Shape)& aShape, double* pTemp)
{

	auto sourceTrsf = m_context->Location(aShape);
	double Rx{ pTemp[0] }, Ry{ pTemp[1] }, Rz{ pTemp[2] };
	Rx = Rx / 180 * M_PI;
	Ry = Ry / 180 * M_PI;
	Rz = Rz / 180 * M_PI;

	//设置欧拉角
	gp_Trsf aTrsf_Rotation;
	gp_Quaternion aQ;
	aQ.SetEulerAngles(gp_YawPitchRoll, Rx, Ry, Rz);
	aTrsf_Rotation.SetRotation(aQ);

	//设置平移向量
	gp_Trsf aTrsf_Translation;
	gp_Vec theVectorOfTrans(pTemp[3], pTemp[4], pTemp[5]);
	aTrsf_Translation.SetTranslation(theVectorOfTrans);
	gp_Trsf trsf = aTrsf_Translation * aTrsf_Rotation;
	SetModelLocation(aShape, trsf);
}

void OccView::angleDebug(const gp_Ax3& FromSystem, const gp_Ax3& ToSystem)//变换前后的坐标系
{
	gp_Trsf trsf;
	trsf.SetTransformation(FromSystem, ToSystem);
	gp_Quaternion quaternion = trsf.GetRotation();//获取四元数，存储了旋转信息
	//gp_Mat mat=quaternion.GetMatrix () ;//获取旋转矩阵
	Standard_Real theAlpha, theBeta, theGamma;
	//从四元数中获取欧拉角，一共有24种，根据需要添加
	quaternion.GetEulerAngles(gp_Intrinsic_XYZ, theAlpha, theBeta, theGamma);
	//与PowerMill中每个数值差一个负号，输出角度
	qDebug() << "position:" << trsf.TranslationPart().X() << "," << trsf.TranslationPart().Y() << "," << trsf.TranslationPart().Z();
	qDebug() << "Angle:" << -theAlpha * 180 / 3.14 << "," << -theBeta * 180 / 3.14 << "," << -theGamma * 180 / 3.14 << endl;
}

void OccView::PartMoveSim()
{

}

void OccView::RobotMoveSim()
{


}

void OccView::toolTrihedronDisplay()
{


#ifdef ER100
	gp_Trsf aCubeTrsf, aCubeTrsf3, aCubeTrsf4, aCubeTrsf5, aCubeTrsf6;

	gp_Trsf rot, tran;
	gp_Vec gv1(gp_Dir(0, 0, 1)), gv12(-GeneralAx6.Direction());
	gp_Quaternion quaternion;
	quaternion.SetRotation(gv1, gv12);
	tran.SetRotation(quaternion);

	gp_Vec loc;
	loc.SetX(GeneralAx6.Location().X());
	loc.SetY(GeneralAx6.Location().Y());
	loc.SetZ(GeneralAx6.Location().Z());
	rot.SetTranslationPart(loc);
	aCubeTrsf = rot * tran;

	tool0Ax2.Transform(aCubeTrsf);
	Handle(Geom_Axis2Placement) TrihedronAxis = new Geom_Axis2Placement(tool0Ax2);
	toolTrihedron = new AIS_Trihedron(TrihedronAxis);
	toolTrihedron->SetDatumPartColor(Prs3d_DP_XAxis, Quantity_NOC_RED2);
	toolTrihedron->SetDatumPartColor(Prs3d_DP_YAxis, Quantity_NOC_GREEN2);
	toolTrihedron->SetDatumPartColor(Prs3d_DP_ZAxis, Quantity_NOC_BLUE2);
	toolTrihedron->SetLabel(Prs3d_DP_XAxis, "X");
	toolTrihedron->SetLabel(Prs3d_DP_YAxis, "Y");
	toolTrihedron->SetLabel(Prs3d_DP_ZAxis, "Z");
	m_context->Display(toolTrihedron, Standard_True);

	RobotAISShape[6]->AddChild(toolTrihedron);



#endif // ER100


}

void OccView::RobotBackHome()
{
	getJoint01CurrentAngle() = getJoint02CurrentAngle() = getJoint03CurrentAngle() = 0;
	getJoint04CurrentAngle() = getJoint05CurrentAngle() = getJoint06CurrentAngle() = 0;
	gp_Ax1 ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	gp_Trsf trans;
	trans.SetRotation(GeneralAx1, getJoint01CurrentAngle());
	m_context->SetLocation(RobotAISShape[1], trans);

	gp_Ax1 ax2(gp_Pnt(260, 0, 675), gp_Dir(0, 1, 0));
	trans.SetRotation(GeneralAx2, getJoint02CurrentAngle());
	m_context->SetLocation(RobotAISShape[2], trans);

	gp_Ax1 ax3(gp_Pnt(260, 0, 1355), gp_Dir(0, 1, 0));
	trans.SetRotation(GeneralAx3, getJoint03CurrentAngle());
	m_context->SetLocation(RobotAISShape[3], trans);

	gp_Ax1 ax4(gp_Pnt(662, 0, 1320), gp_Dir(1, 0, 0));
	trans.SetRotation(GeneralAx4, getJoint04CurrentAngle());
	m_context->SetLocation(RobotAISShape[4], trans);

	gp_Ax1 ax5(gp_Pnt(930, 0, 1320), gp_Dir(0, 1, 0));
	trans.SetRotation(GeneralAx5, getJoint05CurrentAngle());
	m_context->SetLocation(RobotAISShape[5], trans);

	gp_Ax1 ax6(gp_Pnt(1088, 0, 1320), gp_Dir(1, 0, 0));
	trans.SetRotation(GeneralAx6, getJoint06CurrentAngle());
	m_context->SetLocation(RobotAISShape[6], trans);

	m_context->UpdateCurrentViewer();

}

void OccView::CameraAnaminationStart()
{



}

void OccView::ButtonAxis01MoveForward()
{
	gp_Trsf trans;
	getJoint01CurrentAngle() = getJoint01CurrentAngle() + deltaAngle;
	auto angle = getJoint01CurrentAngle() - Joint01OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx1, getJoint01CurrentAngle());
	m_context->SetLocation(RobotAISShape[1], trans);
	m_context->UpdateCurrentViewer();

	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis02MoveForward()
{
	gp_Trsf trans;
	getJoint02CurrentAngle() = getJoint02CurrentAngle() + deltaAngle;
	auto angle = getJoint02CurrentAngle() - Joint02OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx2, getJoint02CurrentAngle());
	m_context->SetLocation(RobotAISShape[2], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis03MoveForward()
{
	gp_Trsf trans;
	getJoint03CurrentAngle() = getJoint03CurrentAngle() + deltaAngle;
	auto angle = getJoint03CurrentAngle() - Joint03OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx3, getJoint03CurrentAngle());
	m_context->SetLocation(RobotAISShape[3], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis04MoveForward()
{
	gp_Trsf trans;
	getJoint04CurrentAngle() = getJoint04CurrentAngle() + deltaAngle;
	auto angle = getJoint04CurrentAngle() - Joint04OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx4, getJoint04CurrentAngle());
	m_context->SetLocation(RobotAISShape[4], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis05MoveForward()
{
	gp_Trsf trans;
	getJoint05CurrentAngle() = getJoint05CurrentAngle() + deltaAngle;
	auto angle = getJoint05CurrentAngle() - Joint05OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx5, getJoint05CurrentAngle());
	m_context->SetLocation(RobotAISShape[5], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis06MoveForward()
{
	gp_Trsf trans;
	getJoint06CurrentAngle() = getJoint06CurrentAngle() + deltaAngle;
	auto angle = getJoint06CurrentAngle() - Joint06OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx6, getJoint06CurrentAngle());
	m_context->SetLocation(RobotAISShape[6], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis01MoveBackward()
{
	gp_Trsf trans;
	getJoint01CurrentAngle() = getJoint01CurrentAngle() - deltaAngle;
	auto angle = getJoint01CurrentAngle() - Joint01OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx1, getJoint01CurrentAngle());
	m_context->SetLocation(RobotAISShape[1], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis02MoveBackward()
{
	gp_Trsf trans;
	getJoint02CurrentAngle() = getJoint02CurrentAngle() - deltaAngle;
	auto angle = getJoint02CurrentAngle() - Joint02OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx2, getJoint02CurrentAngle());
	m_context->SetLocation(RobotAISShape[2], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis03MoveBackward()
{
	gp_Trsf trans;
	getJoint03CurrentAngle() = getJoint03CurrentAngle() - deltaAngle;
	auto angle = getJoint03CurrentAngle() - Joint03OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx3, getJoint03CurrentAngle());
	m_context->SetLocation(RobotAISShape[3], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis04MoveBackward()
{
	gp_Trsf trans;
	getJoint04CurrentAngle() = getJoint04CurrentAngle() - deltaAngle;
	auto angle = getJoint04CurrentAngle() - Joint04OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx4, getJoint04CurrentAngle());
	m_context->SetLocation(RobotAISShape[4], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis05MoveBackward()
{
	gp_Trsf trans;
	getJoint05CurrentAngle() = getJoint05CurrentAngle() - deltaAngle;
	auto angle = getJoint05CurrentAngle() - Joint05OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx5, getJoint05CurrentAngle());
	m_context->SetLocation(RobotAISShape[5], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::ButtonAxis06MoveBackward()
{
	gp_Trsf trans;
	getJoint06CurrentAngle() = getJoint06CurrentAngle() - deltaAngle;
	auto angle = getJoint06CurrentAngle() - Joint06OriginAngle;
	Ui::PILimit(angle);
	trans.SetRotation(GeneralAx6, getJoint06CurrentAngle());
	m_context->SetLocation(RobotAISShape[6], trans);
	m_context->UpdateCurrentViewer();
	qDebug() << "CurrentAngle:" << getJoint01CurrentAngle() * 180 / PI << "," << getJoint02CurrentAngle() * 180 / PI << "," << getJoint03CurrentAngle() * 180 / PI << ","
		<< getJoint04CurrentAngle() * 180 / PI << "," << getJoint05CurrentAngle() * 180 / PI << "," << getJoint06CurrentAngle() * 180 / PI;
}

void OccView::setLinkPm(std::array<double, 7 * 16> link_pm)
{
	gp_Trsf transformation;
	for (int i = 1; i < 7; ++i) {
		transformation.SetValues(link_pm[i * 16], link_pm[i * 16 + 1], link_pm[i * 16 + 2], link_pm[i * 16 + 3] * 1000,
			link_pm[i * 16 + 4], link_pm[i * 16 + 5], link_pm[i * 16 + 6], link_pm[i * 16 + 7] * 1000,
			link_pm[i * 16 + 8], link_pm[i * 16 + 9], link_pm[i * 16 + 10], link_pm[i * 16 + 11] * 1000);
		std::cout << "position:" << "x " << link_pm[i * 16 + 3] << " y " << link_pm[i * 16 + 7] << " z " << link_pm[i * 16 + 11] << std::endl;
		m_context->SetLocation(RobotAISShape[i], transformation);
	}
}

void OccView::setLinkPq(std::array<double, 7 * 7> link_pq)
{
	gp_Trsf transformation;
	for (int i = 1; i < 7; ++i) {
		transformation.SetTransformation( 
			gp_Quaternion(link_pq[i * 7 + 3], link_pq[i * 7 + 4], link_pq[i * 7 + 5], link_pq[i * 7 + 6]), 
			gp_Vec(link_pq[i * 7] * 1000, link_pq[i * 7 + 1] * 1000, link_pq[i * 7 + 2] * 1000));
			m_context->SetLocation(RobotAISShape[i], transformation);
	}
}


void OccView::setAngle(double angle)
{
	gp_Trsf trans1, trans2, trans3, trans4, trans5, trans6;
	trans1.SetRotation(GeneralAx1, angle);
	trans2.SetRotation(GeneralAx2, angle);
	trans3.SetRotation(GeneralAx3, angle);
	trans4.SetRotation(GeneralAx4, angle);
	trans5.SetRotation(GeneralAx5, angle);
	trans6.SetRotation(GeneralAx6, angle);

	m_context->SetLocation(RobotAISShape[1], trans1);
	m_context->SetLocation(RobotAISShape[2], trans2);
	m_context->SetLocation(RobotAISShape[3], trans3);
	m_context->SetLocation(RobotAISShape[4], trans4);
	m_context->SetLocation(RobotAISShape[5], trans5);
	m_context->SetLocation(RobotAISShape[6], trans6);
	m_context->UpdateCurrentViewer();
}

void OccView::setAngle(double* angle)
{
	gp_Trsf trans1, trans2, trans3, trans4, trans5, trans6;
	trans1.SetRotation(GeneralAx1, angle[0]);
	trans2.SetRotation(GeneralAx2, angle[1]);
	trans3.SetRotation(GeneralAx3, angle[2]);
	trans4.SetRotation(GeneralAx4, angle[3]);
	trans5.SetRotation(GeneralAx5, angle[4]);
	trans6.SetRotation(GeneralAx6, angle[5]);

	getJoint01CurrentAngle() = angle[0];
	getJoint02CurrentAngle() = angle[1];
	getJoint03CurrentAngle() = angle[2];
	getJoint04CurrentAngle() = angle[3];
	getJoint05CurrentAngle() = angle[4];
	getJoint06CurrentAngle() = angle[5];

	m_context->SetLocation(RobotAISShape[1], trans1);
	m_context->SetLocation(RobotAISShape[2], trans2);
	m_context->SetLocation(RobotAISShape[3], trans3);
	m_context->SetLocation(RobotAISShape[4], trans4);
	m_context->SetLocation(RobotAISShape[5], trans5);
	m_context->SetLocation(RobotAISShape[6], trans6);
	m_context->UpdateCurrentViewer();
	qDebug() << "slot:" << angle[0];

	//gp_Trsf transformation;
	//for (int i = 1; i < 7; ++i) {
	//	transformation.SetValues(link_pm[i * 16], link_pm[i * 16 + 1], link_pm[i * 16 + 2], link_pm[i * 16 + 3] * 1000,
	//		link_pm[i * 16 + 4], link_pm[i * 16 + 5], link_pm[i * 16 + 6], link_pm[i * 16 + 7] * 1000,
	//		link_pm[i * 16 + 8], link_pm[i * 16 + 9], link_pm[i * 16 + 10], link_pm[i * 16 + 11] * 1000);
	//	//std::cout << "position:" << "x " << link_pm[i * 16 + 3] << " y " << link_pm[i * 16 + 7] << " z " << link_pm[i * 16 + 11] << std::endl;
	//	m_context->SetLocation(RobotAISShape[i], transformation);
	//}
	//gp_Trsf transformation;
	//for (int i = 1; i < 7; ++i) {

	//	link_pq[i * 7] = link_pq[i * 7] * 1000;
	//	link_pq[i * 7 + 1] = link_pq[i * 7 + 1] * 1000;
	//	link_pq[i * 7 + 2] = link_pq[i * 7 + 2] * 1000;
	//	std::cout << link_pq[i * 7] << " " << link_pq[i * 7 + 1] << " " << link_pq[i * 7 + 2] << " " << link_pq[i * 7 + 3] << " " << link_pq[i * 7 + 4] << " " << link_pq[i * 7 + 5] << " " << link_pq[i * 7 + 6] << " " << std::endl;
	//	transformation.SetTranslation(gp_Vec(link_pq[i * 7], link_pq[i * 7 + 1], link_pq[i * 7 + 2]));
	//	transformation.SetRotation(gp_Quaternion(link_pq[i * 7 + 3], link_pq[i * 7 + 4], link_pq[i * 7 + 5], link_pq[i * 7 + 6]));
	//	m_context->SetLocation(RobotAISShape[i], transformation);
	//}
}

void OccView::setVisiable(nameState name, bool state)
{
	if (name == nameState::joint1) {
		if (state == true) {
			m_context->Display(RobotAISShape[1], Standard_True);
			m_context->Display(RobotAISShape[0], Standard_True);
		}
		else {
			m_context->Erase(RobotAISShape[1], Standard_True);
			m_context->Erase(RobotAISShape[0], Standard_True);
		}
	}

	if (name == nameState::tool) {
		if (state == true) {
			m_context->Display(ToolAISShape, Standard_True);
		}
		else {
			m_context->Erase(ToolAISShape, Standard_True);
		}
	}
}

void OccView::setExternalToolEnable(bool enable)
{
	ExternalToolEnable = enable;
}

void OccView::ButtonPartCoorOK()
{
	Eigen::Matrix4d originMatrix;
	double origin_pe[6]{ originPart0Coordinate.x ,originPart0Coordinate.y,originPart0Coordinate.z,originPart0Coordinate.rx,originPart0Coordinate.ry,originPart0Coordinate.rz };
	Ui::s_pe2pm(origin_pe, originMatrix, "123");
	qDebug() << "originPart0Coordinate:" << originPart0Coordinate.x << "," << originPart0Coordinate.y << "," << originPart0Coordinate.z << "," << originPart0Coordinate.rx << "," << originPart0Coordinate.ry << "," << originPart0Coordinate.rz;
	Eigen::Matrix4d currentMatrix;
	double current_pe[6]{ getPartCoor().x,getPartCoor().y,getPartCoor().z,getPartCoor().rx,getPartCoor().ry,getPartCoor().rz };
	Ui::s_pe2pm(current_pe, currentMatrix, "123");


	double jointTool0[6]{ getJoint01CurrentAngle() * PI / 180,
						  getJoint02CurrentAngle() * PI / 180,
						  getJoint03CurrentAngle() * PI / 180,
						  getJoint04CurrentAngle() * PI / 180,
						  getJoint05CurrentAngle() * PI / 180,
						  getJoint06CurrentAngle() * PI / 180 };

	robot_tool0_matrix = Ui::ESTUN_ER100_3000_MDH_Forward(jointTool0);

	robot_tool0_matrix(0, 3) = robot_tool0_matrix(0, 3) * 1000;
	robot_tool0_matrix(1, 3) = robot_tool0_matrix(1, 3) * 1000;
	robot_tool0_matrix(2, 3) = robot_tool0_matrix(2, 3) * 1000;


	Ui::qDebugMatrix4d(robot_tool0_matrix, "robot_tool0_matrix");
	auto transMatrix = robot_tool0_matrix * currentMatrix * originMatrix.inverse();
	gp_Trsf transpart;
	double pe_00[6]{ 0.0 };
	Ui::s_pm2pe(transMatrix, pe_00, "123");
	gp_Trsf trans_00, rot_00;

	qDebug() << "ButtonPartCoorOK:" << "pe_00:";
	qDebug() << pe_00[0];
	qDebug() << pe_00[1];
	qDebug() << pe_00[2];

	qDebug() << pe_00[3] * 180 / PI;
	qDebug() << pe_00[4] * 180 / PI;
	qDebug() << pe_00[5] * 180 / PI;

	trans_00.SetTranslationPart(gp_Vec(pe_00[0], pe_00[1], pe_00[2]));
	gp_Quaternion origin_qua;
	origin_qua.SetEulerAngles(gp_EulerSequence::gp_Intrinsic_XYZ, pe_00[3], pe_00[4], pe_00[5]);
	rot_00.SetRotation(origin_qua);
	transpart = trans_00 * rot_00;

	m_context->SetLocation(partTrihedron, transpart);
	m_context->Update(partTrihedron, true);
}

void OccView::ButtonToolCoorOK()
{
	gp_Ax1 ax1(gp_Pnt(930, 0, 1300), gp_Dir(0, 1, 0));
	gp_Trsf trans, rot, transs;

	trans.SetTranslationPart(gp_Vec(getToolCoor().x, getToolCoor().y, getToolCoor().z));
	gp_Quaternion qua;
	qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, getToolCoor().rx, getToolCoor().ry, getToolCoor().rz);
	rot.SetRotation(qua);
	transs = trans * rot;//先平移再按照当前的矩阵旋转；
	//transs = rot * trans;//先平移再按照世界坐标系旋转；



	//trans.SetTranslationPart(gp_Vec(getToolCoor().x - originTool0Coordinate.x, getToolCoor().y - originTool0Coordinate.y, getToolCoor().z - originTool0Coordinate.z));
	//gp_Quaternion qua;
	//qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, getToolCoor().rx - originTool0Coordinate.rx, getToolCoor().ry - originTool0Coordinate.ry, getToolCoor().rz - originTool0Coordinate.rz);
	//rot.SetRotation(qua);
	//transs = rot * trans;



	//gp_Trsf current_trans, current_rot, current_transs;
	//gp_Trsf origin_trans, origin_rot, origin_transs;
	//current_trans.SetTranslationPart(gp_Vec(getToolCoor().x, getToolCoor().y, getToolCoor().z));
	//gp_Quaternion current_qua;
	//current_qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, getToolCoor().rx, getToolCoor().ry, getToolCoor().rz);
	//current_rot.SetRotation(current_qua);
	//current_transs = current_trans * current_rot;

	//origin_trans.SetTranslationPart(gp_Vec(originTool0Coordinate.x, originTool0Coordinate.y, originTool0Coordinate.z));
	//gp_Quaternion origin_qua;
	//origin_qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, originTool0Coordinate.rx, originTool0Coordinate.ry, originTool0Coordinate.rz);
	//origin_rot.SetRotation(origin_qua);
	//origin_transs = origin_trans * origin_rot;

	//auto origin_matrix = Ui::transf2Matrix(origin_transs);
	//auto current_matrix = Ui::transf2Matrix(current_transs);


	gp_Trsf transpart;
	Eigen::Matrix4d originMatrix;
	double origin_pe[6]{ originTool0Coordinate.x ,originTool0Coordinate.y,originTool0Coordinate.z,originTool0Coordinate.rx,originTool0Coordinate.ry,originTool0Coordinate.rz };
	Ui::s_pe2pm(origin_pe, originMatrix, "123");
	qDebug() << "originTool0Coordinate:" << originTool0Coordinate.x << "," << originTool0Coordinate.y << "," << originTool0Coordinate.z << "," << originTool0Coordinate.rx << "," << originTool0Coordinate.ry << "," << originTool0Coordinate.rz;
	Eigen::Matrix4d currentMatrix;
	double current_pe[6]{ getToolCoor().x,getToolCoor().y,getToolCoor().z,getToolCoor().rx,getToolCoor().ry,getToolCoor().rz };
	Ui::s_pe2pm(current_pe, currentMatrix, "123");

	auto transMatrix = currentMatrix * originMatrix.inverse();

	Ui::qDebugMatrix4d(currentMatrix, "currentMatrix");
	Ui::qDebugMatrix4d(originMatrix, "originMatrix");
	Ui::qDebugMatrix4d(originMatrix.inverse(), "originMatrix.inverse()");
	Ui::qDebugMatrix4d(transMatrix, "transMatrix");

	double pe_00[6];
	Ui::s_pm2pe(transMatrix, pe_00, "123");
	gp_Trsf trans_00, rot_00;
	//trans_00.SetTranslationPart(gp_Vec(getToolCoor().x - originTool0Coordinate.x, getToolCoor().y - originTool0Coordinate.y, getToolCoor().z - originTool0Coordinate.z));
	trans_00.SetTranslationPart(gp_Vec(pe_00[0], pe_00[1], pe_00[2]));
	gp_Quaternion origin_qua;
	origin_qua.SetEulerAngles(gp_EulerSequence::gp_Intrinsic_XYZ, pe_00[3], pe_00[4], pe_00[5]);
	rot_00.SetRotation(origin_qua);
	transpart = trans_00 * rot_00;
	m_context->SetLocation(toolTrihedron, transpart);

	qDebug() << "deltaX:" << pe_00[0];
	qDebug() << "deltaY:" << pe_00[1];
	qDebug() << "deltaZ:" << pe_00[2];
	qDebug() << "deltaRX:" << pe_00[3];
	qDebug() << "deltaRY:" << pe_00[4];
	qDebug() << "deltaRZ:" << pe_00[5];

	m_context->Update(toolTrihedron, true);

	//gp_Trsf current_trans, current_rot, current_transs;
	//current_trans.SetTranslationPart(gp_Vec(getToolCoor().x, getToolCoor().y, getToolCoor().z));
	//gp_Quaternion current_qua;
	//current_qua.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, getToolCoor().rx, getToolCoor().ry, getToolCoor().rz);
	//current_rot.SetRotation(current_qua);
	//current_transs = current_trans * current_rot;

	//gp_Trsf transpart = current_transs;




	//qDebug() << " transpart.TranslationPart():" << transpart.TranslationPart().X() << "," << transpart.TranslationPart().Y() << "," << transpart.TranslationPart().Z();
	//double RX, RY, RZ;
	//transpart.GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, RX, RY, RZ);

	//qDebug() << " transpart.TranslationPart():" << RX << "," << RY << "," << RZ;

	//double Rx, Ry, Rz;

	//gp_Trsf current_trans00, current_rot00, current_transs00;
	//current_trans00.SetTranslationPart(gp_Vec(-originTool0Coordinate.x, -originTool0Coordinate.y, -originTool0Coordinate.z));
	//gp_Quaternion current_qua00;
	//current_qua00.SetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, - originTool0Coordinate.rx, - originTool0Coordinate.ry, - originTool0Coordinate.rz);
	//current_rot00.SetRotation(current_qua00);
	//current_transs00 = current_rot00* current_trans00;

	//auto loc = m_context->Location(toolTrihedron);
	//loc.Transformation().GetRotation().GetEulerAngles(gp_EulerSequence::gp_Extrinsic_XYZ, Rx, Ry, Rz);
	//qDebug() << loc.Transformation().TranslationPart().X() << loc.Transformation().TranslationPart().Y() << loc.Transformation().TranslationPart().Z();
	//qDebug() << Rx; qDebug() << Ry; qDebug() << Rz;
}

void OccView::ButtonFirstCurve()
{
	m_context->Deactivate();
	auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_EDGE);
	m_context->Activate(PartAISShape, aSubShapeSelMode);
	selectFirstCurve = true;
}

void OccView::ButtonSecondCurve()
{
	m_context->Deactivate();
	auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_EDGE);
	m_context->Activate(PartAISShape, aSubShapeSelMode);
	selectSecondCurve = true;
}

void OccView::ButtonPlainSelect()
{
	m_context->Deactivate();
	auto aSubShapeSelMode = AIS_Shape::SelectionMode(TopAbs_FACE);
	m_context->Activate(PartAISShape, aSubShapeSelMode);
	selectFaces = true;
}

/********CAM计算*************/
void OccView::ButtonPointsCal()
{
	double aFirst;
	double aLast;
	auto edge = TopoDS::Edge(PairfirstCurve.second);
	auto lastedge = TopoDS::Edge(PairsecondCurve.second);
	auto face = TopoDS::Face(PairPlains.back().second);

	Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, aFirst, aLast);
	Handle(Geom_TrimmedCurve) TrimmedCurve = new Geom_TrimmedCurve(curve, aFirst, aLast);
	Handle(Geom_TrimmedCurve) trimmer02 = new Geom_TrimmedCurve(TrimmedCurve, aFirst + 1, aLast - 1);
	Handle(Geom_BSplineCurve) PCurve = GeomConvert::CurveToBSplineCurve(TrimmedCurve);

	/**********平面和曲线相交****************/
	{



		for (int j = 1; j < 20; j++) {


			Standard_Real firstParam = curve->FirstParameter();
			Standard_Real lastParam = curve->LastParameter();
			Standard_Real params[4];
			gp_Pnt points[4];
			for (int k = 0; k < 4; k++) {
				params[k] = (lastParam - firstParam) / 4 * k + firstParam;
				curve->D0(params[k], points[k]);
			}

			gp_Dir dir1(points[2].X() - points[1].X(), points[2].Y() - points[1].Y(), points[2].Z() - points[1].Z());
			gp_Dir dir2(points[3].X() - points[2].X(), points[3].Y() - points[2].Y(), points[3].Z() - points[2].Z());
			gp_Dir dir3;

			gp_Pnt pnt00;
			pnt00.SetX(points[0].X());
			pnt00.SetY(points[0].Y());
			pnt00.SetZ(points[0].Z() + j * 10);
			dir3 = dir1 ^ dir2;



			gp_Pln apln(pnt00, dir3);
			Handle(Geom_Plane) gepln = new Geom_Plane(apln);
			Handle(AIS_Plane) planeAIS = new AIS_Plane(gepln);
			//m_context->Display(planeAIS, true);

			PartAISShape->AddChild(planeAIS);


			BOOL index_;
			BRepAlgoAPI_Section section(face, apln, index_);

			BRepAlgoAPI_Common com;

			section.ComputePCurveOn2(true);
			section.Approximation(true);
			section.Build();
			qDebug() << "index_:" << index_;
			if (index_) {
				auto shape = section.Shape();


				qDebug() << "shape.NbChildren():" << shape.NbChildren();
				auto shapeEdge = TopoDS::Compound(shape);

				Handle(AIS_Shape) aishape = new AIS_Shape(shape);
				aishape->SetColor(Quantity_NOC_BLACK);
				m_context->Display(aishape, true);

				PartAISShape->AddChild(aishape);

				double aaFirst;
				double aaLast;

				for (TopExp_Explorer e(shape, TopAbs_EDGE); e.More(); e.Next())
				{
					TopoDS_Edge aedge = TopoDS::Edge(e.Current());
					qDebug() << "succeed";

					Handle(Geom_Curve) aacurve = BRep_Tool::Curve(aedge, aaFirst, aaLast);
					Handle(Geom_TrimmedCurve) aaTrimmedCurve = new Geom_TrimmedCurve(aacurve, aaFirst, aaLast);
					Handle(Geom_BSplineCurve) aaPCurve = GeomConvert::CurveToBSplineCurve(aaTrimmedCurve);

					Standard_Real aaafirst = aaPCurve->FirstParameter();
					Standard_Real aaalast = aaPCurve->LastParameter();
					for (int deta = 0; deta < 5; deta++) {
						Standard_Real data = aaafirst + (aaalast - aaafirst) / 4 * deta;
						gp_Pnt pdata;
						gp_Vec vec1, vec2;
						aaPCurve->D2(data, pdata, vec1, vec2);
						TopoDS_Vertex pvertex = BRepBuilderAPI_MakeVertex(pdata);
						Handle(AIS_Shape) pshape = new AIS_Shape(pvertex);
						pshape->SetColor(Quantity_NOC_YELLOW);
						m_context->Display(pshape, Standard_True);

						PartAISShape->AddChild(pshape);


						IntCurvesFace_ShapeIntersector* intsec = new IntCurvesFace_ShapeIntersector();
						intsec->Load(face, 1);
						gp_Lin normLine1(pdata, gp_Dir(vec2));
						intsec->Perform(normLine1, -1, 1);
						auto Udata = intsec->UParameter(1);
						auto Vdata = intsec->VParameter(1);
						BRepGProp_Face analysisFace(face);
						gp_Pnt p1; gp_Vec vecc;


						analysisFace.Normal(Udata, Vdata, p1, vecc);
						pointVecs.push_back({ p1,vecc });
						gp_Lin normLine2(p1, gp_Dir(vecc));
						TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(normLine2, 0, 20);
						Handle(AIS_Shape) vecshape = new AIS_Shape(anEdge2);
						vecshape->SetColor(Quantity_NOC_BLUE1);
						m_context->Display(vecshape, Standard_True);

						PartAISShape->AddChild(vecshape);

					}

				}

			}

		}

	}

}



void OccView::ConstructRobot(Assemly_Tree& tree)
{

}

void OccView::InstallFilters(TopAbs_ShapeEnum shapeenum)
{
	auto aSubShapeSelMode = AIS_Shape::SelectionMode(shapeenum);
	m_context->Activate(aSubShapeSelMode);
	qDebug() << "m_context->Activate(aSubShapeSelMode);";
}

void OccView::UninstallFilters(TopAbs_ShapeEnum shapeenum)
{
	auto aSubShapeSelMode = AIS_Shape::SelectionMode(shapeenum);
	m_context->Deactivate(aSubShapeSelMode);
	qDebug() << "m_context->Deactivate(aSubShapeSelMode);";
}

void OccView::setJointAngle(nameState joint, double angle)
{
	if (joint == nameState::joint1) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx1, angle);
		m_context->SetLocation(RobotAISShape[1], trans);
		m_context->UpdateCurrentViewer();

		Joint01CurrentAngle = angle;
	}

	if (joint == nameState::joint2) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx2, angle);
		m_context->SetLocation(RobotAISShape[2], trans);
		m_context->UpdateCurrentViewer();

		Joint02CurrentAngle = angle;
	}


	if (joint == nameState::joint3) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx3, angle);
		m_context->SetLocation(RobotAISShape[3], trans);
		m_context->UpdateCurrentViewer();

		Joint03CurrentAngle = angle;
	}

	if (joint == nameState::joint4) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx4, angle);
		m_context->SetLocation(RobotAISShape[4], trans);
		m_context->UpdateCurrentViewer();

		Joint04CurrentAngle = angle;
	}

	if (joint == nameState::joint5) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx5, angle);
		m_context->SetLocation(RobotAISShape[5], trans);
		m_context->UpdateCurrentViewer();

		Joint05CurrentAngle = angle;
	}

	if (joint == nameState::joint6) {
		gp_Trsf trans;
		Ui::PILimit(angle);
		trans.SetRotation(GeneralAx6, angle);
		m_context->SetLocation(RobotAISShape[6], trans);
		m_context->UpdateCurrentViewer();

		Joint06CurrentAngle = angle;
	}
}

void OccView::ReadFile(QString aFilePath, Handle(Document)doc)
{
	STEPCAFControl_Reader reader;
	reader.SetColorMode(true);
	reader.SetNameMode(true);
	reader.ReadFile(aFilePath.toUtf8());


	/*******注册progressbar***********/
	OccProgressIndicator* indicat = new OccProgressIndicator();
	QObject::connect(indicat, SIGNAL(updateProgress(int)), this, SLOT(importValue(int)));
	Handle_XSControl_WorkSession ws = reader.Reader().WS();
	ws->MapReader()->SetProgress(indicat);


	bool yes = reader.Transfer(doc);
	if (yes)
	{

		TDF_Label mainLabel = doc->Main();
		Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
		Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(mainLabel);
		{
			TDF_LabelSequence tdfLabels;
			ShapeTool->GetFreeShapes(tdfLabels);   //获取装配体和组件对应名称
			NodeId RootNodeID = 0;
			TDF_Label Label = tdfLabels.Value(1);
			Ui::deepBuildAssemblyTree(RootNodeID, Label, doc->docTree);

			/******获取机器人的shape*****/

			TDF_LabelSequence components;
			XCAFDoc_ShapeTool::GetComponents(Label, components);
			for (int i = 1; i <= components.Length(); i++) {
				TDF_Label Label00 = components.Value(i);
				auto shape = ShapeTool->GetShape(Label00);
				RobotAISShape[i - 1] = new AIS_Shape(shape);
				m_context->Display(RobotAISShape[i - 1], true);
			}

			//RobotAISShape[5]->AddChild(RobotAISShape[6]);
			//RobotAISShape[4]->AddChild(RobotAISShape[5]);
			//RobotAISShape[3]->AddChild(RobotAISShape[4]);
			//RobotAISShape[2]->AddChild(RobotAISShape[3]);
			//RobotAISShape[1]->AddChild(RobotAISShape[2]);
			//RobotAISShape[0]->AddChild(RobotAISShape[1]);
		}
		initRobot();

	}
}



