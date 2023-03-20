#include "Kmeans.h"

/*****************************************************************************************
********************************* ��ȡ�����ļ����� ***************************************
*****************************************************************************************/
bool ReadTestFile(list <strMyRecord*>* pRecordList)
{
	FILE *pInFile;                                     //��¼�ļ���ָ��
	int iTestCount;                                    //����ļ��е�������Ŀ
	char szBuf[MAX_BUF_SIZE];                          //���ļ�����  MAX_BUF_SIZE = 512
	strMyRecord* pRecord;                              //������¼��ָ��

	string strTemp;
	char szSeps[] = ",\r\n";
	
	cout<<"Start reading records from test file!"<<endl;
	outfile<<"Start reading records from test file!"<<endl;	
	
	if ((pInFile = fopen("corrected_datatreat", "r")) == NULL)
	{
		cout<<"Open Test file faied !"<<endl;
		return false;
	}
	else
	{
		iTestCount = 0;
		while (fgets(szBuf, MAX_BUF_SIZE, pInFile) != NULL)
		{
			if(++iTestCount%10000 == 0)
				cout<<setiosflags(ios::left)<<setw(8)<<iTestCount<<"  lines have read ..."<<endl;

			pRecord = new  strMyRecord;
			//02 Э������
			strTemp = strtok(szBuf, szSeps);
			pRecord->fProtocolType = (float)atof(strTemp.c_str());
			//03 ��������
			strTemp = strtok(NULL, szSeps);
			pRecord->fService = (float)atof(strTemp.c_str());
			//04 ״̬��־
			strTemp = strtok(NULL, szSeps);
			pRecord->fStatusFlag = (float)atof(strTemp.c_str());
			//05 Դ��Ŀ���ֽ���
			strTemp = strtok(NULL, szSeps);
			pRecord->fSrcBytes = (float)atof(strTemp.c_str());
			//06 Ŀ�ĵ�Դ�ֽ���
			strTemp = strtok(NULL, szSeps);
			pRecord->fDestBytes = (float)atof(strTemp.c_str());
			//11 ��¼ʧ�ܴ���
			strTemp = strtok(NULL, szSeps);
			pRecord->fFailedLogins = (float)atof(strTemp.c_str());
			//14 �Ƿ���root�û�Ȩ�޲�Ҫ
			strtok(NULL, szSeps);
			//16 root�û�Ȩ�޴�ȡ����
			strTemp = strtok(NULL, szSeps);
			pRecord->fNumofRoot = (float)atof(strTemp.c_str());
			//22 �Ƿ���guest�û���¼��Ҫ
			strtok(NULL, szSeps);
			//23 2����������ͬ������Ŀ
			strTemp = strtok(NULL, szSeps);
			pRecord->fCount = (float)atof(strTemp.c_str());
			//24 2����������ͬ�˿���Ŀ
			strTemp = strtok(NULL, szSeps);
			pRecord->fSrvCount = (float)atof(strTemp.c_str());
			//27 "REJ"���������������
			strTemp = strtok(NULL, szSeps);
			pRecord->fRerrorRate = (float)atof(strTemp.c_str());
			//29 ���ӵ���ͬ�˿�������
			strTemp = strtok(NULL, szSeps);
			pRecord->fSameSrvRate = (float)atof(strTemp.c_str());
			//30 ���ӵ���ͬ�˿�������
			strTemp = strtok(NULL, szSeps);
			pRecord->fDiffSrvRate = (float)atof(strTemp.c_str());
			//33 ��ͬĿ�ĵ���ͬ�˿�������
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvCount = (float)atof(strTemp.c_str());
			//34 ��ͬĿ�ĵ���ͬ�˿�����������
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSameSrvRate = (float)atof(strTemp.c_str());
			//35 ��ͬĿ�ĵز�ͬ�˿�����������
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostDiffSrvRate = (float)atof(strTemp.c_str());
			//36 ��ͬĿ�ĵ���ͬԴ�˿����ӱ���
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSameSrcPortRate = (float)atof(strTemp.c_str());
			//37 ��ͬ����������ͬ�˿ڱ���
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvDiffHostRate = (float)atof(strTemp.c_str());
			//39 ���ӵ�ǰ������S0����ı���
			strTemp = strtok(NULL, szSeps);
			pRecord->fDstHostSrvSerrorRate = (float)atof(strTemp.c_str());
			//42 ���ͱ�ǩ
			strTemp = strtok(NULL, szSeps);
			pRecord->iLabel = atoi(strTemp.c_str());
			
			//������β�������¼
		  pRecordList->push_back(pRecord);
		}
		
		cout<<iTestCount<<" Records have read from test file!"<<endl;			
		outfile<<iTestCount<<" Records have read from test file!"<<endl;		
		return true;
	}
}

/*****************************************************************************************
**************************** ��Label��int����ת��Ϊstring���� ****************************
*****************************************************************************************/
string LabelInttoStr(int i)
{
	 string strLabel;
   switch(i)
   {
    	case 0:
    		strLabel = "normal";
    		break;
    	case 1:
    		strLabel = "dos";
    		break;
    	case 2:
    		strLabel = "probe";
    		break;
    	case 3:
    		strLabel = "ur2";
    		break;
    	case 4:
    		strLabel = "r2l";
    		break;
    	default:
    		strLabel = "!!ERROR!!";
    		break;    		
    }
    return strLabel;	
}

/*****************************************************************************************
**************************************** Main���� **************************************** 
*****************************************************************************************/
int main()
{		
	int Kvalue;                                        //Kֵ
	int iRightRcdNum;                                  //��¼������ȷ�ļ�¼��
	int TestRcdNum;                                    //�μӼ��ļ�¼����
	string strTrueLabel,strPreLabel;                   //��ʵ��ǩ��Ԥ���ǩ
	
	strMyRecord* pRecord;                              //������¼��ָ��
	list <strMyRecord*>* pTestRcdList;                 //������������
	list<strMyRecord*>::iterator TestListIter;         //��¼����ĵ�����

	ClusterNode* pClusterNode;	                     //����ڵ�ָ��
	ClusterTree* pClusterTree;                         //������
	
	/*************************************************************************************
	*********** PART1 ����K-Means�㷨����ѵ�����ݼ����е������࣬������������ ************
	*************************************************************************************/
	
	//����������
	//����KMeans�������
	//��ȡѵ�����еļ�¼
	//�û�����Kֵ��ֱ�ӽ�Kֵ����Ϊ5
	//��Kֵ��¼����־�ļ���	  
	//����Kmeans�㷨  
    	//��ӡ������
    	//����������ӡ����־�ļ���

	/****************************************************************************************
	******* PART2 ���þ����� �Բ������ݼ��е����ݽ�������Ԥ�⣬�������׼ȷ�ʺͻ�������******
	****************************************************************************************/  
  
 
  	//��ȡ�����ļ�
  	//����һ����������
  	//Ԥ����ȷ�ļ�¼������Ϊ0
  	//������¼������Ϊ0
    	//����������������Ϊÿһ�������ҵ���������
    	//ͳ�Ʒ�����ȷ�ļ�¼��
    	//���»�������
    	//�������¼д��result.txt�ļ���
      //��ӡ����
    	//������ȷ������
    	//��ӡ��������    

  }
}
