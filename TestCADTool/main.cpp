#include "CADModel.h"
using namespace CADModelTool;
#include <direct.h>

void TestXml01()
{
	/*rootNode*/
	CADComponent* pRootNode = nullptr;
	{
		CADPlane plane1(CADPoint{ 0,0,0 }, CADPoint{ 1,0,0 });
		BaseAsmElem* pElem1 = new PlaneElem("PIN.step", plane1);
		CADPlane plane2(CADPoint{ 0,0,0 }, CADPoint{ 1,0,0 });
		BaseAsmElem* pElem2 = new PlaneElem("SUB_ASM1.ASM", plane2);
		CADConstraint cons1(CADConsType::MATE, pElem1, pElem2);
		std::vector<CADConstraint> vecCons;
		vecCons.push_back(cons1);
		pRootNode = new CADComponent("ASM0001.ASM", vecCons);
	}

	//subNode1
	{
		CADMatrix matrix{ CADVector {},CADVector{},CADVector{} };
		CADPartInfo partInfo("PIN.step", matrix);
		CADComponent* pPinNode = new CADComponent("PIN.PRT", partInfo);
		pRootNode->vecSubNodes.push_back(pPinNode);
	}


	//subNode2
	{
		CADPlane plane1(CADPoint{ 0,0,0 }, CADPoint{ 1,0,0 });
		BaseAsmElem* pElem1 = new PlaneElem("CYLINDER.step", plane1);
		CADPlane plane2(CADPoint{ 0,0,0 }, CADPoint{ 1,0,0 });
		BaseAsmElem* pElem2 = new PlaneElem("PIN.step", plane2);
		CADConstraint cons1(CADConsType::MATE, pElem1, pElem2);
		std::vector<CADConstraint> vecCons;
		vecCons.push_back(cons1);
		CADComponent* pAsm0001Node = new CADComponent("SUB_ASM1.ASM", vecCons);
		pRootNode->vecSubNodes.push_back(pAsm0001Node);

		{
			CADMatrix matrix{ CADVector {},CADVector{},CADVector{} };
			CADPartInfo partInfo("CYLINDER.step", matrix);
			CADComponent* pPinNode = new CADComponent("CYLINDER.PRT", partInfo);
			pAsm0001Node->vecSubNodes.push_back(pPinNode);
		}

		{
			CADMatrix matrix{ CADVector {},CADVector{},CADVector{} };
			CADPartInfo partInfo("PIN.step", matrix);
			CADComponent* pPinNode = new CADComponent("PIN.PRT", partInfo);
			pAsm0001Node->vecSubNodes.push_back(pPinNode);
		}
	}
	char tmp[256];
	auto err = _getcwd(tmp, 256);
	std::string xmlPath = std::string(tmp) + "\\1.xml";
	WriteModelToXml(pRootNode, xmlPath);
}
void TestXml02()
{
	char tmp[256];
	auto err = _getcwd(tmp, 256);
	std::string xmlPath = std::string(tmp) + "\\1.xml";

	CADComponent* pRootNode = nullptr;
	ReadModeFromXml(xmlPath, &pRootNode);

	std::string copyXmlPath = std::string(tmp) + "\\copy.xml";
	WriteModelToXml(pRootNode, copyXmlPath);
}

int main()
{
	//TestXml01();
	TestXml02();
	return 0;
}