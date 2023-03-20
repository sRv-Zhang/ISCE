#include "Commom.h"

extern ofstream outfile;

/**************************************************************************************
************************************* ��  ClusterNode *********************************
**************************************************************************************/

class ClusterNode
{
public:
	//���캯��
	ClusterNode()
	{
		int i;
		//��ָ����ΪNULL
		pParentNode = NULL;
		for(i=0;i < MAXLABEL;i++)
		{
			pChildNode[i] = NULL;         //����ָ����ΪNULL
			iLabelNum[i] = 0;             //��ǩ��Ŀ����Ϊ0
		}
		for(i=0;i<MAXDIMENSION;i++)
		{
			fCenter[i] = 0;               //�������ĵ����Ϊ0
		}
		ClusterResult = 0;              //�ۺ϶�����Ϊ0
		IsClusterOK = false;            //��Ϊ�����Ͼ����׼
		IsLeaf = 0;                     //����Ϊ��Ҷ�ӽڵ�
	};
	
	//���������¼���ýڵ����ĵľ���
	float CalCenterDistance(strMyRecord* pRecord);
	//��ú���i��ָ��
	ClusterNode* GetChildNode(int i);
	//��ñ��ڵ�ľ����ǩ
	int GetClusterNodeLabel();
	//�ݹ麯�������Ըýڵ�Ϊ���������У���������ݼ�¼����ľ���ڵ�
	ClusterNode* GetNearestCluster(strMyRecord* pRecord);
	//�ݹ麯������ӡ�ڵ���Ϣ
	void Print();
	//���������������־�ļ���
	void PrintLog();
	
	
public:
	//����ڵ������
	float fCenter[MAXDIMENSION];
	//����ڵ��·��
	string strPath;
	//ָ���������ڵ�ĸ��ڵ��ָ��
	ClusterNode* pParentNode;
	//ָ���������ڵ�ĺ��ӽڵ��ָ��
	ClusterNode* pChildNode[MAXLABEL];	
	//�ۺ϶�
	float ClusterResult;
	//�ۺϽ���Ƿ���ϱ�׼
	bool IsClusterOK;
	//�ж��Ƿ�ΪҶ�ӽڵ㣬���ж��Ƿ����ھ����������������ֹ��Ҷ��
	//0: ��Ҷ�ӽڵ㡢 1��Ҷ�ӽڵ��Ҿ����������� �� 2��Ҷ�ӽڵ��Ҿ������������
	int IsLeaf;
	//��¼���ַ����ǩ����Ŀ
	int iLabelNum[MAXLABEL];
};

/**************************************************************************************
************************************* ��  ClusterTree *********************************
**************************************************************************************/
class ClusterTree
{
public:
	//���캯��
	ClusterTree()
	{
		pRootNode = new ClusterNode();
		pRootNode->strPath = "0";
	}
	
	//�������
	void InsertNode(ClusterNode* pParent,ClusterNode* pNode,int i);
	//�ҵ��������¼��������ľ���
	ClusterNode* FindNearestCluster(strMyRecord* pRecord);
	//��ø��ڵ�
	ClusterNode* GetRootNode();	
  //��ӡ������
	void Print();
	//���������������־�ļ���
	void PrintLog();
		
private:
	//���ڵ�
	ClusterNode* pRootNode;
};

