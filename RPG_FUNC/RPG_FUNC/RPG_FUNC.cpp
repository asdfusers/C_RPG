// RPG_FUNC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;


#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMORE_MAX 3
#define LEVEL_MAX 10



const int g_iLevelUpExp[LEVEL_MAX] = { 1000, 10000, 20000, 35000, 50000, 70000,
100000, 150000, 200000, 400000 };



enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK


};
enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
}; 

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};


struct _tagItem
{
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH]; // ������ ����

};
struct _tagInventory
{
	_tagItem   tItem[INVENTORY_MAX];
	int         iItemCount;
	int         i_Gold;
};
struct _tagPlayer
{
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJob;
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHp;
	int iHpMax;
	int iMp;
	int iMpMax;
	int iExp;
	int iLevel;
	_tagItem tEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
	_tagInventory tInventory;
};

struct _tagMonster
{
	char strName[NAME_SIZE];
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHp;
	int iHpMax;
	int iMp;
	int iMpMax;
	int iLevel;
	int iExp;
	int iGoldMin;
	int iGoldMax;

};

struct _tagLevelUpStatus
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHpMin;
	int iHpMax;
	int iMpMin;
	int iMpMax;
};



_tagLevelUpStatus g_tLvupTable[JOB_END - 1] = {};


int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; 
	}

	return iInput;
}

int OutputMainMenu()
{
	system("cls");
	cout << "*************************�κ�*****************************" << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iMenu = InputInt();
	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;

}

int OutputMapMenu()
{
	system("cls");
	cout << "*************************��*****************************" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷΰ��� " << endl;
	cout << "���� �����ϼ��� : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;

	return iMenu;

}


int SelectJob()
{
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		iJob = InputInt();


		 if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;

	}
	return iJob;
}
void SetPlayer(_tagPlayer* pPlayer)
{


	cout << "�̸� : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SelectJob();

	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.i_Gold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "���");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHpMax = 500;
		pPlayer->iHp = 500;
		pPlayer->iMp = 100;
		pPlayer->iMpMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "�ü�");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHpMax = 400;
		pPlayer->iHp = 400;
		pPlayer->iMp = 200;
		pPlayer->iMpMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "������");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHpMax = 300;
		pPlayer->iHp = 300;
		pPlayer->iMp = 300;
		pPlayer->iMpMax = 300;
		break;
	}
}

_tagMonster CreateMonster(char* pName, int iAttackMin,
	int iAttackMax, int iArmorMin, int iArmorMax, int iHp,
	int iMp, int iLevel, int iExp, int iGoldMin, int iGoldMax)
{
	_tagMonster tMonster = {};
	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHp = iHp;
	tMonster.iHpMax = iHp;
	tMonster.iMp = iMp;
	tMonster.iMpMax = iMp;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMax = iGoldMax;
	tMonster.iGoldMin = iGoldMin;
	
	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr)
{
	pMonsterArr[0] = CreateMonster("���", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("Ʈ��", 80, 130, 60, 50, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("�巡��", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);

}

void OutputBattleTag(int iMenu)
{
	switch (iMenu)
	{
	case MT_EASY:
		cout << "*************************����*****************************" << endl;
		break;

	case MT_NORMAL:
		cout << "*************************����*****************************" << endl;
		break;

	case MT_HARD:
		cout << "*************************�����*****************************" << endl;
		break;
	}
}

void OutputPlayer(_tagPlayer* pPlayer)
{
	//�÷��̾� ������ ���
	cout << "==================== Player ====================" << endl;
	cout << "�̸� : " << pPlayer->strJobName << "\t ���� : " <<
		pPlayer->strJobName << endl;
	cout << "���� : " << pPlayer->iLevel << "\t ����ġ : " <<
		pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	if (pPlayer->bEquip[EQ_WEAPON] == true)

	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else
	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << " - " << pPlayer->iAttackMax;
	}

	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t���� : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax;
	}
	else
	{
		cout << "\t���� : " << pPlayer->iArmorMin << " - " << pPlayer->iArmorMax << endl;;
	}


	cout << "ü�� : " << pPlayer->iHp << " / " << pPlayer->iHpMax <<
		"\t ���� : " << pPlayer->iMp << " / " << pPlayer->iMpMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "���� ���� : " << pPlayer->tEquip[EQ_WEAPON].strName;
	else
		cout << "���� ���� : ����";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t ���� �� : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t ���� �� : ����" << endl;



	cout << "������� : " << pPlayer->tInventory.i_Gold << " Gold" << endl;

}

void OutputMonster(_tagMonster* pMonster)
{
	//���� ���� ��� 

	cout << "==================== Monster ====================" << endl;
	cout << "�̸� : " << pMonster->strName << "\t ���� : " <<
		pMonster->iLevel << endl;
	cout << "���ݷ� : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\t ���� : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "ü�� : " << pMonster->iHp << " / " << pMonster->iHpMax <<
		"\t ���� : " << pMonster->iMp << " / " << pMonster->iMpMax << endl;
	cout << "ȹ�� ����ġ : " << pMonster->iExp << "\t ȹ���� : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;

}

int OutputBattleMenu()
{

	cout << "1. ���� " << endl;
	cout << "2. �������� " << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;

}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster)
{

	int iAttackMin = pPlayer->iAttackMin;
	int iAttackMax = pPlayer->iAttackMax;

	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
		pMonster->iArmorMin;

	int iDamage = iAttack - iArmor;

	iDamage = iDamage < 1 ? 1 : iDamage;

	//���� HP�� ����
	pMonster->iHp -= iDamage;
	cout << pPlayer->strName << "��" << pMonster->strName <<
		"���� " << iDamage << " ���ظ� �������ϴ�. " << endl;

	//���Ͱ� ������
	if (pMonster->iHp <= 0)
	{
		cout << pMonster->strName << " ���Ͱ� ����Ͽ����ϴ�. " << endl;
		pPlayer->iExp += pMonster->iExp;
		int iGold = (rand() % (pMonster->iGoldMax - pMonster->iGoldMin + 1) + pMonster->iGoldMin);
		pPlayer->tInventory.i_Gold += iGold;

		cout << pMonster->iExp << " ����ġ�� ȹ���Ͽ����ϴ�. " << endl;
		cout << iGold << " Gold�� ȹ���Ͽ����ϴ�. " << endl;

		pMonster->iHp = pMonster->iHpMax;
		pMonster->iMp = pMonster->iMpMax;

		//������ üũ
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];
			++pPlayer->iLevel;

			cout << "������ �Ͽ����ϴ�. " << endl;

			int iJobIndex = pPlayer->eJob - 1;

			int iHpUp = rand() % (g_tLvupTable[iJobIndex].iHpMax - g_tLvupTable[iJobIndex].iHpMin - 1)
				+ g_tLvupTable[iJobIndex].iHpMin;
			int iMpUp = rand() % (g_tLvupTable[iJobIndex].iMpMax - g_tLvupTable[iJobIndex].iMpMin - 1)
				+ g_tLvupTable[iJobIndex].iMpMin;


			pPlayer->iAttackMin += g_tLvupTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += g_tLvupTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += g_tLvupTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += g_tLvupTable[iJobIndex].iArmorMax;

			pPlayer->iHpMax += iHpUp;
			pPlayer->iMpMax += iMpUp;

			pPlayer->iHp = pPlayer->iHpMax;
			pPlayer->iMp = pPlayer->iMpMax;
		}

		return;
	}

	// ���Ͱ� ����ִٸ� �÷��̾ ����


	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
		pMonster->iAttackMin;

	int iArmorMin = pPlayer->iArmorMin;
	int iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) +
		iArmorMin;

	iDamage = iAttack - iArmor;

	iDamage = iDamage < 1 ? 1 : iDamage;

	//�÷��̾� HP ����
	pPlayer->iHp -= iDamage;
	cout << pMonster->strName << "��" << pPlayer->strName <<
		"���� " << iDamage << " ���ظ� �������ϴ�. " << endl;

	//�÷��̾ �׾�����
	if (pPlayer->iHp <= 0)
	{
		cout << pMonster->strName << " �÷��̾ ����Ͽ����ϴ�. " << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.i_Gold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.i_Gold -= iGold;

		cout << iExp << " ����ġ�� �Ҿ����ϴ�. " << endl;
		cout << iGold << " Gold�� �Ҿ����ϴ�. " << endl;

		pPlayer->iMp = pPlayer->iMpMax;
		pPlayer->iHp = pPlayer->iHpMax;

	}
	system("pause");
}
void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu)
{
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true)
	{
		system("cls");
		OutputBattleTag(iMenu);

		//�÷��̾� ���
		OutputPlayer(pPlayer);

		//���� ���
		OutputMonster(&tMonster);

		switch (OutputBattleMenu())
		{
		case BATTLE_ATTACK:
			Battle(pPlayer, &tMonster);
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

//Map�� ���õ� ������ ó��
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr)
{
	bool bLoop = true;

	while (bLoop)
	{
		int iMenu = OutputMapMenu();

		if (MT_BACK == iMenu)
			return;
		
		//������ ����.
		RunBattle(pPlayer, pMonsterArr, iMenu);
	}

}

_tagLevelUpStatus CreateLvUpStatus(int iAttackMin, int iAttackMax,
	int iArmorMin, int iArmorMax, int iHpMin, int iHpMax, int iMpMin, int iMpMax)
{
	_tagLevelUpStatus tStatus = {};


	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMin;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHpMin = iHpMin;
	tStatus.iHpMax = iHpMax;
	tStatus.iMpMin = iMpMin;
	tStatus.iMpMax = iMpMax;


	return tStatus;

}

int OutputStoreMenu()
{
	system("cls");
	cout << "************************* ���� *****************************" << endl;
	cout << "1. �������" << endl;
	cout << "2. ������" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int  iMenu = InputInt();

	if (iMenu <= SM_NONE || iMenu > SM_BACK)
		return SM_NONE;

	return iMenu;

}

int OutputStoreItemList(_tagInventory* pInventory,  _tagItem* pStore, int iItemCount)
{
	for (int i = 0; i < iItemCount; i++)
	{
		cout << "[" << i + 1 << " ] ";
		cout << "���� �̸� : " << pStore[i].strName << "\t ���� Ÿ�� : " <<
			pStore[i].strTypeName << "\t ���� ���� ���� : " << pStore[i].iPrice << endl;
		cout << "���� �Ǹ� ���� : " << pStore[i].iSell << "\t ���� ���� : " << pStore[i].strDesc << endl << endl;

	}

	cout << iItemCount + 1 << ". �ڷΰ���" << endl;
	cout << "���� �ݾ� : " << pInventory->i_Gold << " Gold" << endl;
	cout << "���� ���� : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "������ �������� �����ϼ��� : ";

	int iMenu = InputInt();
	
	if (iMenu < 1 || iMenu > iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	while (true)
	{
		system("cls");

		switch (iStoreType)
		{
		case SM_WEAPON:
			cout << "*************************** ������� ***************************" << endl;
			break;
		case SM_ARMOR:
			cout << "*************************** �� ***************************" << endl;
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount);
	
		if (iInput == INT_MAX)
		{
			cout << "�߸� �Է��Ͽ����ϴ�. " << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1)
			break;


		int iIndex = iInput - 1;

		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "������ �� á���ϴ�. " << endl;
			system("pause");
			continue;
		}
		else if (pInventory->i_Gold < pStore[iIndex].iPrice)
		{
			cout << "���� �ݾ��� �����մϴ�. " << endl;
			system("pause");
			continue;
		}

		pInventory->tItem[pInventory->iItemCount] =
			pStore[iIndex];
		++pInventory->iItemCount;

		pInventory->i_Gold -= pStore[iIndex].iPrice;

		cout << pStore[iIndex].strName << " �������� �����Ͽ����ϴ�. " << endl;
		system("pause");

	
	}

}
void RunStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor)
{
	while (true)
	{
		switch (OutputStoreMenu())
		{
		case SM_WEAPON:
			BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			BuyItem(pInventory, pArmor, STORE_ARMORE_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}
}

_tagItem CreateItem(char* pName, ITEM_TYPE eType, int iMin, int iMax, int iPrice, int iSell, char* pDesc)
{
	_tagItem tItem = {};
	strcpy_s(tItem.strName, pName);
	strcpy_s(tItem.strDesc, pDesc);

	tItem.eType = eType;

	switch (eType)
	{
	case IT_WEAPON:
		strcpy_s(tItem.strTypeName, "����");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "��");
		break;
	}

	tItem.iMin = iMin;
	tItem.iMax = iMax;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;
	

	return tItem;
}

int OutputInventory(_tagPlayer* pPlayer)
{
	system("cls");
	cout << "****************************** ���� ******************************";

	OutputPlayer(pPlayer);

	for (int i = 0; i < pPlayer->tInventory.iItemCount; ++i)
	{
		cout << "[" << i + 1 << " ] ";
		cout << "���� �̸� : " << pPlayer->tInventory.tItem[i].strName << "\t ���� Ÿ�� : " <<
			pPlayer->tInventory.tItem[i].strTypeName << "\t ���� ���� ���� : " << pPlayer->tInventory.tItem[i].iPrice << endl;
		cout << "���� �Ǹ� ���� : " << pPlayer->tInventory.tItem[i].iSell << "\t ���� ���� : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
	}

	cout << pPlayer->tInventory.iItemCount + 1 << ". �ڷΰ���" << endl;
	cout << "������ �������� �����ϼ��� : ";
	
	int iMenu = InputInt();

	if (iMenu > 1 || iMenu > pPlayer->tInventory.iItemCount + 1)
		return INT_MAX;
	
	return iMenu;



}

EQUIP ComputeEquipType(ITEM_TYPE eType)
{
	EQUIP eq;

	switch (eType)
	{
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	default:
		break;
	}
	return eq;

}
void RunInventory(_tagPlayer* pPlayer)
{
	while (true)
	{
		int iInput = OutputInventory(pPlayer);
	
		if (iInput == INT_MAX)
			continue;
		else if (iInput == pPlayer->tInventory.iItemCount + 1)
			break;

		int idx = iInput - 1;

		EQUIP eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

		if (pPlayer->bEquip[eq] == true)
		{
			_tagItem tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}

		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; i++)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}
			--pPlayer->tInventory.iItemCount;

			pPlayer->bEquip[eq] = true;
		}
		cout << pPlayer->tEquip[eq].strName << " �������� �����Ͽ����ϴ�." << endl;
		system("pause");

	}



}

int main()
{
	srand((unsigned int)time(0));
	
	//������ �����Ҷ� �÷��̾� ������ ����
	_tagPlayer tPlayer = {};

	SetPlayer(&tPlayer);

	//���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};
	SetMonster(tMonsterArr);

	
	
	g_tLvupTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	g_tLvupTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	g_tLvupTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	//�������� �Ǹ��� ������ ����� �����Ѵ�.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMORE_MAX] = {};

	tStoreWeapon[0] = CreateItem("���", IT_WEAPON, 5, 10, 1000, 500, "������ ���� Į");
	tStoreWeapon[1] = CreateItem("�۱�", IT_WEAPON, 20, 30, 7000, 3500, "¯¯�� Ȱ");
	tStoreWeapon[2] = CreateItem("������", IT_WEAPON, 90, 150, 30000, 15000, "������ ���� ������");

	tStoreArmor[0] = CreateItem("õ����", IT_ARMOR, 2, 5, 1000, 500, "õ���� ���� ����");
	tStoreArmor[1] = CreateItem("���װ���", IT_ARMOR, 10, 20, 7000, 3500, "���� �������� ���� ����");
	tStoreArmor[2] = CreateItem("Ǯ�÷���Ʈ�Ƹ�", IT_ARMOR, 70, 90, 30000, 15000, "��ö�� ���� �Ǳݰ���");


	bool bLoop = true;
	
	while (bLoop)
	{
		switch (OutputMainMenu())
		{
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr); // �� ���� ���� ó��
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}


    return 0;
}

