#include "CurveIKCmd.h"

#include <maya/MGlobal.h>

//#include <maya/MFnPlugin.h>

#include <maya/MArgList.h>
#include <maya/MObject.h>
//
#include <maya/MPointArray.h>


#include<maya/MItDag.h>
#include<maya/MFnIkHandle.h>
#include<maya/MFnDagNode.h>
#include<maya/MFnIkSolver.h>
#include<maya/MDagPath.h>
#include<maya/MPlugArray.h>
#include<maya/MFnDependencyNode.h>

#include <maya/MFnIkEffector.h>
#include <maya/MFnIkJoint.h>

#include <maya/MSelectionList.h>

#include <vector>

using namespace std;
//#include "MyLoadFileToString.h"

CurveIKCmd::CurveIKCmd() : MPxCommand()
{
}

CurveIKCmd::~CurveIKCmd()
{
}



static MVector getPosition(MFnNurbsCurve & curve, double uVal)
{
	//MPoint minPos = MPoint(0, 0, 0);
	//MPoint maxPos = MPoint(10, 10, 10);
	//return (minPos + uVal * (maxPos - minPos));

	MPoint p;
	//curve.getPointAtParam(uVal * (double)(curve.numCVs() - 1), p);

	double u = curve.findParamFromLength(uVal * curve.length());
	curve.getPointAtParam(u, p);

	

	return p;
}



//IK handle

//MStatus CurveIKCmd::doIt(const MArgList& args)
//{
//	MStatus stat;
//
//	//test
//	MString rootName, endEffectorName;
//	MSelectionList curveList;
//	for (int i = 0; i < args.length(); i++)
//	{
//		if (MString("-root") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			rootName = args.asString(++i, &stat);
//		}
//		else if (MString("-end") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			endEffectorName = args.asString(++i, &stat);
//		}
//		else if (MString("-curve") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			//endEffectorName = args.asString(++i, &stat);
//		}
//		else if (MString("-ratio") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			//endEffectorName = args.asString(++i, &stat);
//		}
//
//		/*
//		if (MString("-step") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			float tmp = args.asDouble(++i, &stat);
//			if (MS::kSuccess == stat)
//			{
//				//default_step_size = tmp;
//			}
//		}
//		else if (MString("-angle") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			double tmp = args.asDouble(++i, &stat);
//			if (MS::kSuccess == stat)
//			{
//				//default_angle = tmp;
//			}
//		}
//		else if (MString("-grammar") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			MString tmp = args.asString(++i, &stat);
//			if (MS::kSuccess == stat)
//			{
//				//grammar = tmp;
//			}
//		}
//		else if (MString("-iterations") == args.asString(i, &stat)
//			&& MS::kSuccess == stat)
//		{
//			int tmp = args.asInt(++i, &stat);
//			if (MS::kSuccess == stat)
//			{
//			}
//		}
//		*/
//	}
//
//	// 1.select curve
//	MSelectionList curve_list;
//	stat = MGlobal::getActiveSelectionList(curve_list);
//	if (MS::kSuccess != stat) {
//		return(stat);
//	}
//	MDagPath path;
//	curve_list.getDagPath(0, path);
//	MFnNurbsCurve nurbCurve(path);
//	
//
//
//	// 2. select joint and create handle
//	//MGlobal::selectByName(skeletonName);
//	//MSelectionList list;
//	//stat = MGlobal::getActiveSelectionList(list);
//	//if (MS::kSuccess != stat) {
//	//	return(stat);
//	//}
//	//list.getDagPath(0, path);
//	//MFn
//
//	//MFnIkHandle fnHandle(it.currentItem());
//
//
//	//MItDag it(MItDag::kDepthFirst, MFn::kIkHandle);
//	//MFnIkHandle fnHandle(it.currentItem());
//	MDagPath rootJointDagPath, leafJointDagPath;
//	{
//		MSelectionList list;
//		MGlobal::selectByName(MString(rootName), MGlobal::kReplaceList);
//		stat = MGlobal::getActiveSelectionList(list);
//		list.getDagPath(0, rootJointDagPath);
//
//		MGlobal::selectByName(MString(endEffectorName), MGlobal::kReplaceList);
//		stat = MGlobal::getActiveSelectionList(list);
//		list.getDagPath(0, leafJointDagPath);
//	}
//	MFnIkHandle fnHandle;
//	fnHandle.create(rootJointDagPath, leafJointDagPath);
//
//
//
//
//
//
//	//MItDag it(MItDag::kDepthFirst, MFn::kIkHandle);
//
//	//MFnIkHandle fnHandle(it.currentItem());
//
//	static std::vector<MPoint> m_localJointsPos;
//
//
//
//	// End-Effector
//	MDagPath endEffectorPath;
//	fnHandle.getEffector(endEffectorPath);
//	MFnIkEffector  fnEffector(endEffectorPath);
//	MPoint effectorPos = fnEffector.rotatePivot(MSpace::kWorld);
//
//	unsigned int numJoints = endEffectorPath.length();
//	std::vector<MDagPath> jointsDagPaths; 
//	jointsDagPaths.reserve(numJoints);
//	while (endEffectorPath.length() > 1)
//	{
//		endEffectorPath.pop();
//		jointsDagPaths.push_back(endEffectorPath);
//	}
//	std::reverse(jointsDagPaths.begin(), jointsDagPaths.end());
//
//	static bool builtLocalSkeleton = false;
//	if (builtLocalSkeleton == false)
//	{
//		for (int jointIdx = 0; jointIdx < jointsDagPaths.size(); ++jointIdx)
//		{
//			MFnIkJoint curJoint(jointsDagPaths[jointIdx]);
//			m_localJointsPos.push_back(curJoint.getTranslation(MSpace::kWorld));
//		}
//		m_localJointsPos.push_back(effectorPos);
//		builtLocalSkeleton = true;
//	}
//
//	MPoint startJointPos = MFnIkJoint(jointsDagPaths.front()).getTranslation(MSpace::kWorld);
//
//	MVector startToEndEff = m_localJointsPos.back() - m_localJointsPos.front();
//	//double curveLength = (getPosition(nurbCurve, 1.0) - getPosition(nurbCurve, 0.0)).length();
//	double curveLength = nurbCurve.length();
//	double chainLength = startToEndEff.length(); // in local space.
//	double stretchFactor = curveLength / chainLength;
//
//	double uVal = 0.0f;
//	MVector jointPosL = m_localJointsPos[0];
//	for (int jointIdx = 0; jointIdx < jointsDagPaths.size(); ++jointIdx)
//	{
//		MFnIkJoint curJoint(jointsDagPaths[jointIdx]);
//
//		MVector curJointPosL = m_localJointsPos[jointIdx];
//
//		double dist = stretchFactor * (curJointPosL - jointPosL).length();
//		uVal = uVal + dist / curveLength;
//
//		MVector curCurveJointPos = getPosition(nurbCurve, uVal);
//		curJoint.setTranslation(curCurveJointPos, MSpace::kWorld);
//		jointPosL = curJointPosL;
//	}
//	MVector effectorCurvePos = getPosition(nurbCurve, 1.0);
//	MVector curCurveJointPos = getPosition(nurbCurve, uVal);
//	MVector effectorVec = (effectorCurvePos - curCurveJointPos).normal();
//	double endJointAngle[3];
//	MVector effectorVecXY = MVector(effectorVec(0), effectorVec(1), 0.0);
//	endJointAngle[2] = effectorVecXY.angle(MVector(1, 0, 0));
//	if ((MVector(1, 0, 0) ^ effectorVecXY) * MVector(0, 0, 1) < 0.0) { endJointAngle[2] = -endJointAngle[2]; }
//	MVector effectorVecXZ = MVector(effectorVec(0), 0.0, effectorVec(2));
//	endJointAngle[1] = effectorVecXZ.angle(MVector(1, 0, 0));
//	if ((MVector(1, 0, 0) ^ effectorVecXZ) * MVector(0, 1, 0) < 0.0) { endJointAngle[1] = -endJointAngle[1]; }
//	endJointAngle[0] = 0.0;
//	MFnIkJoint curJoint(jointsDagPaths.back()); curJoint.setRotation(endJointAngle, curJoint.rotationOrder());
//	return MS::kSuccess;
//
//
//}


// FK
MStatus CurveIKCmd::doIt(const MArgList& args)
{

	MStatus stat;

	//test
	MString rootName, endEffectorName;
	MSelectionList curveList;
	for (int i = 0; i < args.length(); i++)
	{
		if (MString("-root") == args.asString(i, &stat)
			&& MS::kSuccess == stat)
		{
			rootName = args.asString(++i, &stat);
		}

		if (MString("-end") == args.asString(i, &stat)
			&& MS::kSuccess == stat)
		{
			endEffectorName = args.asString(++i, &stat);
		}
	}

	// 1.select curve
	MSelectionList curve_list;
	stat = MGlobal::getActiveSelectionList(curve_list);
	if (MS::kSuccess != stat) {
		return(stat);
	}
	MDagPath path;
	curve_list.getDagPath(0, path);
	MFnNurbsCurve nurbCurve(path);

	// 2. select joint and create handle
	//MGlobal::selectByName(skeletonName);
	//MSelectionList list;
	//stat = MGlobal::getActiveSelectionList(list);
	//if (MS::kSuccess != stat) {
	//	return(stat);
	//}
	//list.getDagPath(0, path);
	//MFn

	//MFnIkHandle fnHandle(it.currentItem());


	//MItDag it(MItDag::kDepthFirst, MFn::kIkHandle);
	//MFnIkHandle fnHandle(it.currentItem());
	MDagPath rootJointDagPath, leafJointDagPath;
	{
		MSelectionList list;
		MGlobal::selectByName(MString(rootName), MGlobal::kReplaceList);
		stat = MGlobal::getActiveSelectionList(list);
		list.getDagPath(0, rootJointDagPath);

		MGlobal::selectByName(MString(endEffectorName), MGlobal::kReplaceList);
		stat = MGlobal::getActiveSelectionList(list);
		list.getDagPath(0, leafJointDagPath);
	}
	//MFnIkHandle fnHandle;
	//fnHandle.create(rootJointDagPath, leafJointDagPath);

	//MItDag it(MItDag::kDepthFirst, MFn::kIkHandle);
	//MFnIkHandle fnHandle(it.currentItem());

	static std::vector<MPoint> m_localJointsPos;

	// End-Effector
	MDagPath endEffectorPath = leafJointDagPath;
	//fnHandle.getEffector(endEffectorPath);
	//MFnIkEffector  fnEffector(endEffectorPath);
	MFnTransform transFn(endEffectorPath, &stat);
	MPoint effectorPos = transFn.translation(MSpace::kWorld);

	unsigned int numJoints = endEffectorPath.length();
	std::vector<MDagPath> jointsDagPaths;
	jointsDagPaths.reserve(numJoints);
	while (endEffectorPath.length() > 1)
	{
		endEffectorPath.pop();
		jointsDagPaths.push_back(endEffectorPath);
	}
	std::reverse(jointsDagPaths.begin(), jointsDagPaths.end());

	static bool builtLocalSkeleton = false;
	if (builtLocalSkeleton == false)
	{
		for (int jointIdx = 0; jointIdx < jointsDagPaths.size(); ++jointIdx)
		{
			//MFnIkJoint curJoint(jointsDagPaths[jointIdx]);
			MFnTransform curTransFn(jointsDagPaths[jointIdx], &stat);
			m_localJointsPos.push_back(curTransFn.getTranslation(MSpace::kWorld));
		}
		m_localJointsPos.push_back(effectorPos);
		builtLocalSkeleton = true;
	}

	MPoint startJointPos = MFnTransform(jointsDagPaths.front()).getTranslation(MSpace::kWorld);

	MVector startToEndEff = m_localJointsPos.back() - m_localJointsPos.front();
	//double curveLength = (getPosition(nurbCurve, 1.0) - getPosition(nurbCurve, 0.0)).length();
	double curveLength = nurbCurve.length();
	double chainLength = startToEndEff.length(); // in local space.
	double stretchFactor = curveLength / chainLength;

	double uVal = 0.0f;
	MVector jointPosL = m_localJointsPos[0];
	for (int jointIdx = 0; jointIdx < jointsDagPaths.size(); ++jointIdx)
	{
		MFnTransform curJoint(jointsDagPaths[jointIdx]);

		MVector curJointPosL = m_localJointsPos[jointIdx];

		double dist = stretchFactor * (curJointPosL - jointPosL).length();
		uVal = uVal + dist / curveLength;

		MVector curCurveJointPos = getPosition(nurbCurve, uVal);
		curJoint.setTranslation(curCurveJointPos, MSpace::kWorld);
		jointPosL = curJointPosL;
	}
	MVector effectorCurvePos = getPosition(nurbCurve, 1.0);
	MVector curCurveJointPos = getPosition(nurbCurve, uVal);
	MVector effectorVec = (effectorCurvePos - curCurveJointPos).normal();
	double endJointAngle[3];
	MVector effectorVecXY = MVector(effectorVec(0), effectorVec(1), 0.0);
	endJointAngle[2] = effectorVecXY.angle(MVector(1, 0, 0));
	if ((MVector(1, 0, 0) ^ effectorVecXY) * MVector(0, 0, 1) < 0.0) { endJointAngle[2] = -endJointAngle[2]; }
	MVector effectorVecXZ = MVector(effectorVec(0), 0.0, effectorVec(2));
	endJointAngle[1] = effectorVecXZ.angle(MVector(1, 0, 0));
	if ((MVector(1, 0, 0) ^ effectorVecXZ) * MVector(0, 1, 0) < 0.0) { endJointAngle[1] = -endJointAngle[1]; }
	endJointAngle[0] = 0.0;
	MFnTransform curJoint(jointsDagPaths.back()); curJoint.setRotation(endJointAngle, curJoint.rotationOrder());

	return MS::kSuccess;
}