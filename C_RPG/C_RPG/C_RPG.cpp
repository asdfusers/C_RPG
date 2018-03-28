// RPG.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	char strDesc[ITEM_DESC_LENGTH]; // 아이템 설명

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

	//레벨업에 필요한 경험치 목록
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




	//게임을 시작할때 플레이어 정보를 설정
	_tagPlayer tPlayer = {};



	//플레이어 이름을 받는다.
 

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
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
		strcpy_s(tPlayer.strJobName, "기사");
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
		strcpy_s(tPlayer.strJobName, "궁수");
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
		strcpy_s(tPlayer.strJobName, "마법사");
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

	//몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	//고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
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

	//트롤 생성
	strcpy_s(tMonsterArr[1].strName, "트롤");
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

	//드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
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

	//상점에서 판매할 아이템 목록을 생성한다.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMORE_MAX] = {};

	//각 아이템 정보를 설정해준다.

	strcpy_s(tStoreWeapon[0].strName, "손도끼");
	strcpy_s(tStoreWeapon[0].strTypeName, "도끼");
	tStoreWeapon[0].eType = IT_WEAPONE;
	tStoreWeapon[0].iMin = 1;
	tStoreWeapon[0].iMax = 3;
	tStoreWeapon[0].iPrice = 3000;
	tStoreWeapon[0].iSell = 2000;
	strcpy_s(tStoreWeapon[0].strDesc, "강력한 도끼");

	strcpy_s(tStoreWeapon[1].strName, "석궁");
	strcpy_s(tStoreWeapon[1].strTypeName, "화살");
	tStoreWeapon[1].eType = IT_WEAPONE;
	tStoreWeapon[1].iMin = 1;
	tStoreWeapon[1].iMax = 3;
	tStoreWeapon[1].iPrice = 4000;
	tStoreWeapon[1].iSell = 3000;
	strcpy_s(tStoreWeapon[1].strDesc, "강력한 화살");

	strcpy_s(tStoreWeapon[2].strName, "구슬지팡이");
	strcpy_s(tStoreWeapon[2].strTypeName, "지팡이");
	tStoreWeapon[2].eType = IT_WEAPONE;
	tStoreWeapon[2].iMin = 2;
	tStoreWeapon[2].iMax = 4;
	tStoreWeapon[2].iPrice = 3500;
	tStoreWeapon[2].iSell = 2400;
	strcpy_s(tStoreWeapon[2].strDesc, "강력한 지팡이");

	strcpy_s(tStoreArmor[0].strName, "황금투구");
	strcpy_s(tStoreArmor[0].strTypeName, "투구");
	tStoreArmor[0].eType = IT_ARMOR;
	tStoreArmor[0].iMin = 1;
	tStoreArmor[0].iMax = 3;
	tStoreArmor[0].iPrice = 1000;
	tStoreArmor[0].iSell = 500;
	strcpy_s(tStoreArmor[0].strDesc, "단단한 투구");

	strcpy_s(tStoreArmor[1].strName, "황금갑옷");
	strcpy_s(tStoreArmor[1].strTypeName, "갑옷");
	tStoreArmor[1].eType = IT_ARMOR;
	tStoreArmor[1].iMin = 1;
	tStoreArmor[1].iMax = 3;
	tStoreArmor[1].iPrice = 2400;
	tStoreArmor[1].iSell = 1500;
	strcpy_s(tStoreArmor[1].strDesc, "단단한 갑옷");

	strcpy_s(tStoreArmor[2].strName, "황금신발");
	strcpy_s(tStoreArmor[2].strTypeName, "신발");
	tStoreArmor[2].eType = IT_ARMOR;
	tStoreArmor[2].iMin = 1;
	tStoreArmor[2].iMax = 3;
	tStoreArmor[2].iPrice = 1000;
	tStoreArmor[2].iSell = 500;
	strcpy_s(tStoreArmor[2].strDesc, "단단한 신발");



	while (true)
	{
		system("cls");
		cout << "*************************로비*****************************" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
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
				cout << "*************************맵*****************************" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기 " << endl;
				cout << "맵을 선택하세요 : ";
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

				//선택한 메뉴에서 1을 뺴주면 몬스터 배열의 인덱스가 됨.
				//해당 맵의 몬스터를 생성
				_tagMonster tMonster = tMonsterArr[iMenu - 1];
				while (true)
				{
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						cout << "*************************쉬움*****************************" << endl;
						break;

					case MT_NORMAL:
						cout << "*************************보통*****************************" << endl;
						break;

					case MT_HARD:
						cout << "*************************어려움*****************************" << endl;
						break;
					}

					//플레이어 정보를 출력
					cout << "==================== Player ====================" << endl;
					cout << "이름 : " << tPlayer.strJobName << "\t 직업 : " <<
						tPlayer.strJobName << endl;
					cout << "레벨 : " << tPlayer.iLevel << "\t 경험치 : " <<
						tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

					if (tPlayer.bEquip[EQ_WEAPON] == true)

					{
						cout << "공격력 : " << tPlayer.iAttackMin << " + " <<
							tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
							tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else
					{
						cout << "공격력 : " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax;
					}

					if (tPlayer.bEquip[EQ_ARMOR] == true)
					{
						cout << "\t방어력 : " << tPlayer.iArmorMin << " + " <<
							tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
							tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax;
					}
					else
					{
						cout << "\t방어력 : " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;;
					}


					cout << "체력 : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
						"\t 마나 : " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON])
						cout << "장착 무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;
					else
						cout << "장착 무기 : 없음";

					if (tPlayer.bEquip[EQ_ARMOR])
						cout << "\t 장착 방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
					else
						cout << "\t 장착 방어구 : 없음" << endl;



					cout << "보유골드 : " << tPlayer.tInventory.i_Gold << " Gold" << endl;


					//몬스터 정보 출력 

					cout << "==================== Monster ====================" << endl;
					cout << "이름 : " << tMonster.strName << "\t 레벨 : " <<
						tMonster.iLevel << endl;
					cout << "공격력 : " << tMonster.iAttackMin << " - " <<
						tMonster.iAttackMax << "\t 방어력 : " << tMonster.iArmorMin <<
						" - " << tMonster.iArmorMax << endl;
					cout << "체력 : " << tMonster.iHp << " / " << tMonster.iHpMax <<
						"\t 마나 : " << tMonster.iMp << " / " << tMonster.iMpMax << endl;
					cout << "획득 경험치 : " << tMonster.iExp << "\t 획득골드 : " <<
						tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					cout << "1. 공격 " << endl;
					cout << "2. 도망가기 " << endl;
					cout << "메뉴를 선택하세요 : ";
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

						//몬스터 HP를 감소
						tMonster.iHp -= iDamage;
						cout << tPlayer.strName << "가" << tMonster.strName <<
							"에게 " << iDamage << " 피해를 입혔습니다. " << endl;

						//몬스터가 죽으면
						if (tMonster.iHp <= 0)
						{
							cout << tMonster.strName << " 몬스터가 사망하였습니다. " << endl;
							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
							tPlayer.tInventory.i_Gold += iGold;

							cout << tMonster.iExp << " 경험치를 획득하였습니다. " << endl;
							cout << iGold << " Gold를 획득하였습니다. " << endl;

							tMonster.iHp = tMonster.iHpMax;
							tMonster.iMp = tMonster.iMpMax;

							//레벨업 체크
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
								++tPlayer.iLevel;

								cout << "레벨업 하였습니다. " << endl;

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

						// 몬스터가 살아있다면 플레이어를 공격


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

						//플레이어 HP 감소
						tPlayer.iHp -= iDamage;
						cout << tMonster.strName << "가" << tPlayer.strName <<
							"에게 " << iDamage << " 피해를 입혔습니다. " << endl;

						//플레이어가 죽었을때
						if (tPlayer.iHp <= 0)
						{
							cout << tMonster.strName << " 플레이어가 사망하였습니다. " << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.i_Gold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.i_Gold -= iGold;

							cout << iExp << " 경험치를 잃었습니다. " << endl;
							cout << iGold << " Gold를 잃었습니다. " << endl;

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
				cout << "************************* 상점 *****************************" << endl;
				cout << "1. 무기상점" << endl;
				cout << "2. 방어구상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요 : ";
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

						cout << "************************* 무기상점 *****************************" << endl;
						//판매 목록을 보여준다.

						for (int i = 0; i < STORE_WEAPON_MAX; i++)
						{
							cout << "[" << i + 1 << " ] ";
							cout << "무기 이름 : " << tStoreWeapon[i].strName << "\t 무기 타입 : " <<
								tStoreWeapon[i].strTypeName << "\t 무기 구매 가격 : " << tStoreWeapon[i].iPrice << endl;
							cout << "무기 판매 가격 : " << tStoreWeapon[i].iSell << "\t 무기 설명 : " << tStoreWeapon[i].strDesc << endl << endl;


						}

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유 금액 : " << tPlayer.tInventory.i_Gold << " Gold" << endl;
						cout << "남은 공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
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
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						int iWeaponIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다. " << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.i_Gold < tStoreWeapon[iWeaponIndex].iPrice)
						{
							cout << "보유 금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreWeapon[iWeaponIndex];
						++tPlayer.tInventory.iItemCount;

						tPlayer.tInventory.i_Gold -= tStoreWeapon[iWeaponIndex].iPrice;

						cout << tStoreWeapon[iWeaponIndex].strName << " 아이템을 구매하였습니다. " << endl;
						system("pause");

					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");

						cout << "************************* 방어구상점 *****************************" << endl;
						//판매 목록을 보여준다.

						for (int i = 0; i < STORE_ARMORE_MAX; i++)
						{
							cout << "[" << i + 1 << " ] ";
							cout << "무기 이름 : " << tStoreArmor[i].strName << "\t 무기 타입 : " <<
								tStoreArmor[i].strTypeName << "\t 무기 구매 가격 : " << tStoreArmor[i].iPrice << endl;
							cout << "무기 판매 가격 : " << tStoreArmor[i].iSell << "\t 무기 설명 : " << tStoreArmor[i].strDesc << endl << endl;


						}

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유 금액 : " << tPlayer.tInventory.i_Gold << " Gold" << endl;
						cout << "남은 공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
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
							cout << "잘못 선택하였습니다. " << endl;
							system("pause");
							continue;
						}

						int iArmoreIndex = iMenu - 1;

						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다. " << endl;
							system("pause");
							continue;
						}
						else if (tPlayer.tInventory.i_Gold < tStoreWeapon[iArmoreIndex].iPrice)
						{
							cout << "보유 금액이 부족합니다. " << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] =
							tStoreArmor[iArmoreIndex];
						++tPlayer.tInventory.iItemCount;

						tPlayer.tInventory.i_Gold -= tStoreArmor[iArmoreIndex].iPrice;

						cout << tStoreArmor[iArmoreIndex].strName << " 아이템을 구매하였습니다. " << endl;
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
				cout << "************************* 가방 *****************************" << endl;
				cout << "==================== Player ====================" << endl;
				cout << "이름 : " << tPlayer.strJobName << "\t 직업 : " <<
					tPlayer.strJobName << endl;
				cout << "레벨 : " << tPlayer.iLevel << "\t 경험치 : " <<
					tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;
				cout << "공격력 : " << tPlayer.iAttackMin << " - " <<
					tPlayer.iAttackMax << "\t 방어력 : " << tPlayer.iArmorMin <<
					" - " << tPlayer.iArmorMax << endl;
				cout << "체력 : " << tPlayer.iHp << " / " << tPlayer.iHpMax <<
					"\t 마나 : " << tPlayer.iMp << " / " << tPlayer.iMpMax << endl;
				cout << "보유골드 : " << tPlayer.tInventory.i_Gold << " Gold" << endl << endl;


				for (int i = 0; i < tPlayer.tInventory.iItemCount; ++i)
				{
					cout << "[" << i + 1 << " ] ";
					cout << "무기 이름 : " << tPlayer.tInventory.tItem[i].strName << "\t 무기 타입 : " <<
						tPlayer.tInventory.tItem[i].strTypeName << "\t 무기 구매 가격 : " << tPlayer.tInventory.tItem[i].iPrice << endl;
					cout << "무기 판매 가격 : " << tPlayer.tInventory.tItem[i].iSell << "\t 무기 설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}

				cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요 : ";
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
					cout << "잘못 선택하였습니다. " << endl;
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
				cout << tPlayer.tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;
				system("pause");
			}
			break;
		default:
			cout << "잘못 선택하셨습니다. " << endl;
			break;
		}
	}

	return 0;
}
