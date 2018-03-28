// RPG.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
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

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPONE,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMORE_MAX 3
#define LEVEL_MAX 10


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
int main()
{
	srand((unsigned int)time(0));

	//�������� �ʿ��� ����ġ ���
	const int iLevelUpExp[LEVEL_MAX] = { 1000, 10000, 20000, 35000, 50000, 70000,
		100000, 150000, 200000, 400000 };


	_tagLevelUpStatus tLvupTable[JOB_END - 1] = {};

	tLvupTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvupTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvupTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvupTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvupTable[JOB_KNIGHT - 1].iHpMin = 50;
	tLvupTable[JOB_KNIGHT - 1].iHpMax = 100;
	tLvupTable[JOB_KNIGHT - 1].iMpMin = 10;
	tLvupTable[JOB_KNIGHT - 1].iMpMax = 20;

	tLvupTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvupTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvupTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvupTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvupTable[JOB_ARCHER - 1].iHpMin = 30;
	tLvupTable[JOB_ARCHER - 1].iHpMax = 60;
	tLvupTable[JOB_ARCHER - 1].iMpMin = 30;
	tLvupTable[JOB_ARCHER - 1].iMpMax = 50;

	tLvupTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvupTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvupTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvupTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvupTable[JOB_WIZARD - 1].iHpMin = 20;
	tLvupTable[JOB_WIZARD - 1].iHpMax = 40;
	tLvupTable[JOB_WIZARD - 1].iMpMin = 50;
	tLvupTable[JOB_WIZARD - 1].iMpMax = 100;




	//������ �����Ҷ� �÷��̾� ������ ����
	_tagPlayer tPlayer = {};



	//�÷��̾� �̸��� �޴´�.
 

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;

	}

	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.i_Gold = 10000;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "���");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHpMax = 500;
		tPlayer.iHp = 500;
		tPlayer.iMp = 100;
		tPlayer.iMpMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "�ü�");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHpMax = 400;
		tPlayer.iHp = 400;
		tPlayer.iMp = 200;
		tPlayer.iMpMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "������");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHpMax = 300;
		tPlayer.iHp = 300;
		tPlayer.iMp = 300;
		tPlayer.iMpMax = 300;
		break;
	}

	//���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	//��� ����
	strcpy_s(tMonsterArr[0].strName, "���");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHp = 100;
	tMonsterArr[0].iHpMax = 100;
	tMonsterArr[0].iMp = 10;
	tMonsterArr[0].iMpMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;

	//Ʈ�� ����
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHp = 2000;
	tMonsterArr[1].iHpMax = 2000;
	tMonsterArr[1].iMp = 100;
	tMonsterArr[1].iMpMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	//�巡�� ����
	strcpy_s(tMonsterArr[2].strName, "�巡��");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHp = 30000;
	tMonsterArr[2].iHpMax = 30000;
	tMonsterArr[2].iMp = 2000;
	tMonsterArr[2].iMpMax = 2000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;

	//�������� �Ǹ��� ������ ����� �����Ѵ�.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMORE_MAX] = {};

	//�� ������ ������ �������ش�.

	strcpy_s(tStoreWeapon[0].strName, "�յ���");
	strcpy_s(tStoreWeapon[0].strTypeName, "����");
	tStoreWeapon[0].eType = IT_WEAPONE;
	tStoreWeapon[0].iMin = 1;
	tStoreWeapon[0].iMax = 3;
	tStoreWeapon[0].iPrice = 3000;
	tStoreWeapon[0].iSell = 2000;
	strcpy_s(tStoreWeapon[0].strDesc, "������ ����");

	strcpy_s(tStoreWeapon[1].strName, "����");
	strcpy_s(tStoreWeapon[1].strTypeName, "ȭ��");
	tStoreWeapon[1].eType = IT_WEAPONE;
	tStoreWeapon[1].iMin = 1;
	tStoreWeapon[1].iMax = 3;
	tStoreWeapon[1].iPrice = 4000;
	tStoreWeapon[1].iSell = 3000;
	strcpy_s(tStoreWeapon[1].strDesc, "������ ȭ��");

	strcpy_s(tStoreWeapon[2].strName, "����������");
	strcpy_s(tStoreWeapon[2].strTypeName, "������");
	tStoreWeapon[2].eType = IT_WEAPONE;
	tStoreWeapon[2].iMin = 2;
	tStoreWeapon[2].iMax = 4;
	tStoreWeapon[2].iPrice = 3500;
	tStoreWeapon[2].iSell = 2400;
	strcpy_s(tStoreWeapon[2].strDesc, "������ ������");

	strcpy_s(tStoreArmor[0].strName, "Ȳ������");
	strcpy_s(tStoreArmor[0].strTypeName, "����");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 1;
	tStoreArmor[0].iMax = 3;
	tStoreArmor[0].iPrice = 1000;
	tStoreArmor[0].iSell = 500;
	strcpy_s(tStoreArmor[0].strDesc, "�ܴ��� ����");

	strcpy_s(tStoreArmor[1].strName, "Ȳ�ݰ���");
	strcpy_s(tStoreArmor[1].strTypeName, "����");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 1;
	tStoreArmor[1].iMax = 3;
	tStoreArmor[1].iPrice = 2400;
	tStoreArmor[1].iSell = 1500;
	strcpy_s(tStoreArmor[1].strDesc, "�ܴ��� ����");

	strcpy_s(tStoreArmor[2].strName, "Ȳ�ݽŹ�");
	strcpy_s(tStoreArmor[2].strTypeName, "�Ź�");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 1;
	tStoreArmor[2].iMax = 3;
	tStoreArmor[2].iPrice = 1000;
	tStoreArmor[2].iSell = 500;
	strcpy_s(tStoreArmor[2].strDesc, "�ܴ��� �Ź�");



	while (true)
	{
		system("cls");
		cout << "*************************�κ�*****************************" << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int iMenu;
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				cout << "*************************��*****************************" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ��� " << endl;
				cout << "���� �����ϼ��� : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				//
				if (iMenu == MT_BACK)
					break;

				//������ �޴����� 1�� ���ָ� ���� �迭�� �ε����� ��.
				//�ش� ���� ���͸� ����
				_tagMonster tMonster = tMonsterArr[iMenu - 1];
				while (true)
				{
					system("cls");
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

					//�÷��̾� ������ ���
					cout << "==================== Player ====================" << endl;
					cout << "�̸� : " << tPlayer.strJobName << "\t ���� : " <<
						tPlayer.strJobName << endl;
					cout << "���� : " << tPlayer.iLevel << "\t ����ġ : " <<
						tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

					if (tPlayer.bEquip[EQ_WEAPON] == true)

					{
						cout << "���ݷ� : " << tPlayer.iAttackMin << " + " <<
							tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else
					{
						cout << "���ݷ� : " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax;
					}

					if (tPlayer.bEquip[EQ_ARMOR] == true)
					{
						cout << "\t���� : " << tPlayer.iArmorMin << " + " <<
							tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax;
					}
					else
					{
						cout << "\t���� : " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;;
					}


					cout << "ü�� : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
						"\t ���� : " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON])
						cout << "���� ���� : " << tPlayer.tEquip[EQ_WEAPON].strName;
					else
						cout << "���� ���� : ����";

					if (tPlayer.bEquip[EQ_ARMOR])
						cout << "\t ���� �� : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
					else
						cout << "\t ���� �� : ����" << endl;



					cout << "������� : " << tPlayer.tInventory.i_Gold << " Gold" << endl;


					//���� ���� ��� 

					cout << "==================== Monster ====================" << endl;
					cout << "�̸� : " << tMonster.strName << "\t ���� : " <<
						tMonster.iLevel << endl;
					cout << "���ݷ� : " << tMonster.iAttackMin << " - " <<
						tMonster.iAttackMax << "\t ���� : " << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << endl;
					cout << "ü�� : " << tMonster.iHp << " / " << tMonster.iHpMax <<
						"\t ���� : " << tMonster.iMp << " / " << tMonster.iMpMax << endl;
					cout << "ȹ�� ����ġ : " << tMonster.iExp << "\t ȹ���� : " <<
						tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					cout << "1. ���� " << endl;
					cout << "2. �������� " << endl;
					cout << "�޴��� �����ϼ��� : ";
					cin >> iMenu;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (iMenu == BATTLE_BACK)
						break;

					switch (iMenu)
					{
					case BATTLE_ATTACK:
					{

						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						if (tPlayer.bEquip[EQ_WEAPON])
						{
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax - iAttackMin + 1) +
							iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) +
							tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;

						iDamage = iDamage < 1 ? 1 : iDamage;

						//���� HP�� ����
						tMonster.iHp -= iDamage;
						cout << tPlayer.strName << "��" << tMonster.strName <<
							"���� " << iDamage << " ���ظ� �������ϴ�. " << endl;

						//���Ͱ� ������
						if (tMonster.iHp <= 0)
						{
							cout << tMonster.strName << " ���Ͱ� ����Ͽ����ϴ�. " << endl;
							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
							tPlayer.tInventory.i_Gold += iGold;

							cout << tMonster.iExp << " ����ġ�� ȹ���Ͽ����ϴ�. " << endl;
							cout << iGold << " Gold�� ȹ���Ͽ����ϴ�. " << endl;

							tMonster.iHp = tMonster.iHpMax;
							tMonster.iMp = tMonster.iMpMax;

							//������ üũ
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
								++tPlayer.iLevel;

								cout << "������ �Ͽ����ϴ�. " << endl;

								int iJobIndex = tPlayer.eJob - 1;

								int iHpUp = rand() % (tLvupTable[iJobIndex].iHpMax - tLvupTable[iJobIndex].iHpMin - 1)
									+ tLvupTable[iJobIndex].iHpMin;
								int iMpUp = rand() % (tLvupTable[iJobIndex].iMpMax - tLvupTable[iJobIndex].iMpMin - 1)
									+ tLvupTable[iJobIndex].iMpMin;


								tPlayer.iAttackMin += tLvupTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvupTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvupTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvupTable[iJobIndex].iArmorMax;

								tPlayer.iHpMax += iHpUp;
								tPlayer.iMpMax += iMpUp;

								tPlayer.iHp = tPlayer.iHpMax;
								tPlayer.iMp = tPlayer.iMpMax;
							}



							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ ����


						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) +
							tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR])
						{
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) +
							iArmorMin;

						iDamage = iAttack - iArmor;

						iDamage = iDamage < 1 ? 1 : iDamage;

						//�÷��̾� HP ����
						tPlayer.iHp -= iDamage;
						cout << tMonster.strName << "��" << tPlayer.strName <<
							"���� " << iDamage << " ���ظ� �������ϴ�. " << endl;

						//�÷��̾ �׾�����
						if (tPlayer.iHp <= 0)
						{
							cout << tMonster.strName << " �÷��̾ ����Ͽ����ϴ�. " << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.i_Gold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.i_Gold -= iGold;

							cout << iExp << " ����ġ�� �Ҿ����ϴ�. " << endl;
							cout << iGold << " Gold�� �Ҿ����ϴ�. " << endl;

							tPlayer.iMp = tPlayer.iMpMax;
							tPlayer.iHp = tPlayer.iHpMax;

						}
						system("pause");
					}
					break;

					}

				}

			}
			break;
		case MM_STORE:
			while (true)
			{
				system("cls");
				cout << "************************* ���� *****************************" << endl;
				cout << "1. �������" << endl;
				cout << "2. ������" << endl;
				cout << "3. �ڷΰ���" << endl;
				cout << "������ �����ϼ��� : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == SM_BACK)
					break;

				switch (iMenu)
				{
				case SM_WEAPON:
					while (true)
					{
						system("cls");

						cout << "************************* ������� *****************************" << endl;
						//�Ǹ� ����� �����ش�.

						for (int i = 0; i < STORE_WEAPON_MAX; i++)
						{
							cout << "[" << i + 1 << " ] ";
							cout << "���� �̸� : " << tStoreWeapon[i].strName << "\t ���� Ÿ�� : " <<
								tStoreWeapon[i].strTypeName << "\t ���� ���� ���� : " << tStoreWeapon[i].iPrice << endl;
							cout << "���� �Ǹ� ���� : " << tStoreWeapon[i].iSell << "\t ���� ���� : " << tStoreWeapon[i].strDesc << endl << endl;


						}

						cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "���� �ݾ� : " << tPlayer.tInventory.i_Gold << " Gold" << endl;
						cout << "���� ���� : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;

						else if (iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1)
						{
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						int iWeaponIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�. " << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.i_Gold < tStoreWeapon[iWeaponIndex].iPrice)
						{
							cout << "���� �ݾ��� �����մϴ�. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iItemCount;

						tPlayer.tInventory.i_Gold -= tStoreWeapon[iWeaponIndex].iPrice;

						cout << tStoreWeapon[iWeaponIndex].strName << " �������� �����Ͽ����ϴ�. " << endl;
						system("pause");

					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");

						cout << "************************* ������ *****************************" << endl;
						//�Ǹ� ����� �����ش�.

						for (int i = 0; i < STORE_ARMORE_MAX; i++)
						{
							cout << "[" << i + 1 << " ] ";
							cout << "���� �̸� : " << tStoreArmor[i].strName << "\t ���� Ÿ�� : " <<
								tStoreArmor[i].strTypeName << "\t ���� ���� ���� : " << tStoreArmor[i].iPrice << endl;
							cout << "���� �Ǹ� ���� : " << tStoreArmor[i].iSell << "\t ���� ���� : " << tStoreArmor[i].strDesc << endl << endl;


						}

						cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "���� �ݾ� : " << tPlayer.tInventory.i_Gold << " Gold" << endl;
						cout << "���� ���� : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (iMenu == STORE_ARMORE_MAX + 1)
							break;

						else if (iMenu < 1 || iMenu > STORE_ARMORE_MAX + 1)
						{
							cout << "�߸� �����Ͽ����ϴ�. " << endl;
							system("pause");
							continue;
						}

						int iArmoreIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�. " << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.i_Gold < tStoreWeapon[iArmoreIndex].iPrice)
						{
							cout << "���� �ݾ��� �����մϴ�. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreArmor[iArmoreIndex];
						++tPlayer.tInventory.iItemCount;

						tPlayer.tInventory.i_Gold -= tStoreArmor[iArmoreIndex].iPrice;

						cout << tStoreArmor[iArmoreIndex].strName << " �������� �����Ͽ����ϴ�. " << endl;
						system("pause");

					}
					break;

				}
			}
			break;
		case MM_INVENTORY:
			while (true)
			{
				system("cls");
				cout << "************************* ���� *****************************" << endl;
				cout << "==================== Player ====================" << endl;
				cout << "�̸� : " << tPlayer.strJobName << "\t ���� : " <<
					tPlayer.strJobName << endl;
				cout << "���� : " << tPlayer.iLevel << "\t ����ġ : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;
				cout << "���ݷ� : " << tPlayer.iAttackMin << " - " <<
					tPlayer.iAttackMax << "\t ���� : " << tPlayer.iArmorMin <<
					" - " << tPlayer.iArmorMax << endl;
				cout << "ü�� : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
					"\t ���� : " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
				cout << "������� : " << tPlayer.tInventory.i_Gold << " Gold" << endl << endl;


				for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i)
				{
					cout << "[" << i + 1 << " ] ";
					cout << "���� �̸� : " << tPlayer.tInventory.tItem[i].strName << "\t ���� Ÿ�� : " <<
						tPlayer.tInventory.tItem[i].strTypeName << "\t ���� ���� ���� : " << tPlayer.tInventory.tItem[i].iPrice << endl;
					cout << "���� �Ǹ� ���� : " << tPlayer.tInventory.tItem[i].iSell << "\t ���� ���� : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}

				cout << tPlayer.tInventory.iItemCount + 1 << ". �ڷΰ���" << endl;
				cout << "������ �������� �����ϼ��� : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (iMenu == tPlayer.tInventory.iItemCount + 1)
					break;

				else if (iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1)
				{
					cout << "�߸� �����Ͽ����ϴ�. " << endl;
					system("pause");
					continue;
				}

				int idx = iMenu - 1;

				EQUIP eq;

				switch (tPlayer.tInventory.tItem[idx].eType)
				{
				case IT_WEAPONE:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				default:
					break;
				}


				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				else
				{
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++)
					{
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}
					--tPlayer.tInventory.iItemCount;

					tPlayer.bEquip[eq] = true;
				}
				cout << tPlayer.tEquip[eq].strName << " �������� �����Ͽ����ϴ�." << endl;
				system("pause");
			}
			break;
		default:
			cout << "�߸� �����ϼ̽��ϴ�. " << endl;
			break;
		}
	}

	return 0;
}
