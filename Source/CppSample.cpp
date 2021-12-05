#include "stdafx.h"
#include "RedisTestSenario.h"
#include "cppRedis.h"

// 테스트용 Redis 서버 IP
string GlobalRedisServerAddress = "127.0.0.1";
// 테스트용 Redis 서버 Port
int GlobalRedisServerPort = 6379;

int GetInput()
{
    int choice;
    cin >> choice;
    return choice;
}

void DisplayMainMenu(RedisTestSenario& senario)
{
    cout << "Select Choise\n";
    cout << "1 - Unit Test\n";
    cout << "2 - Thread Loop Test\n";
    cout << "3 - Thread Loop Test Stop\n";
    cout << "9 - Quit\n";
    cout << format("info. Redis:{},{} Test Thread Loop Count[{}]\n", GlobalRedisServerAddress, GlobalRedisServerPort, senario.GetThreadTestCount());
    cout << "Selection: ";
}

int main()
{
    int selectMenu = 0;

    RedisTestSenario senario;
    senario.Setup(GlobalRedisServerAddress, GlobalRedisServerPort, 5);

    do
    {
        system("cls");
        DisplayMainMenu(senario);
        selectMenu = GetInput();

        switch (selectMenu)
        {
        case 1: senario.StartUnitTest(); break;
        case 2: senario.StartThreadLoopTest(); break;
        case 3: senario.Stop(); break;
        default: break;
        }
    } while (selectMenu != 9);
    
    system("PAUSE");
}