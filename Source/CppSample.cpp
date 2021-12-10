#include "stdafx.h"
#include "RedisTestSenario.h"
#include "cppRedis.h"

//TODO
/*
이 코드는 포트폴리오 라는 전제하에. 코멘트를 드렸습니다.

아직 뵙지 못한분의 코드에 코멘트를 다는것이 저에게도 큰 부담이었음을 이해해 주시기 바랍니다.
동의하기 어려운 부분이 있을 수 있습니다.

표현상의 미숙함으로 인해 마음에 상처를 받으실 수 있으나.
모든 코멘트는 나쁜의도가 없었음을 이해 해 주시기 바랍니다.

어디까지나 포트폴리오 관점에서의 제 개인 의견이므로.
부담 갖지 마시고. 채택/거부 하시면 됩니다
첨부한 의견은 모든 클래스/변수에 적용 되는 부분이니.
셀프 코드리뷰를 한번 해보시기를 권해 드립니다.
 */

//TODO
/*
포트폴리오의 경우는 다운로드 받고 솔루션을 열었을때
warning 이나 error없이 깨끗하게 실행 되는것이 좋습니다.
리뷰어에게 좋은 인상을 남기는것이 목표이므로.
불필요한 신경을 쓰이게 하지 않는것이 좋습니다.
cppRedis 의 경우는 lib 로 만드셔서. 제출 하시는것이 좋겠습니다.
실제 제출 하실때는 다른사람의 자리에서 테스트를 해보시고 제출 하시기를 권합니다.
*/

//TODO
/*
맞춤법은 첫인상에서 큰 비중이 있습니다.보조툴(ex > resharper)를 적극 활용하시는것이 좋겠습니다.(senario, Choise 등)
*/

//TODO
/*
변함이 없는 모든 변수에는 const, constexpr 처리를 반드시 하는것이 좋겠습니다.
ex > GlobalRedisServerAddress, GlobalRedisServerPort
*/
// 테스트용 Redis 서버 IP
string GlobalRedisServerAddress = "127.0.0.1";
// 테스트용 Redis 서버 Port
int GlobalRedisServerPort = 6379;

int GetInput()
{
    //TODO
    //변수 초기화 하는 습관을 가지시는것을 권합니다.
    //이 함수는 대단히 심플하여. 동의하기 어려우시겠지만.
    //현대 프로그래밍은 협업 기본이며, 내 코드는 언나 유지보수가 일어납니다.
    //타인이 수정중 실수 하지 않도록.
	//C++을 사용하는 이상, 초기화를 습관으로 만드는것은 대단히 중요합니다.
    int choice;
    cin >> choice;
    return choice;
}

void DisplayMainMenu(RedisTestSenario& senario)
{
    //TODO
    //cout 의 페어는 endl 입니다. \n 으로 마무리 하는 방식은 좋지 않습니다.
    //여러 문장을 출력 하시려다 보니 채택 하셨으리라 생각 합니다만.
    //이 케이스는 는 한번의 cout 으로 문장을 찍어내는것이 적합해 보입니다.

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

        //TODO
        /*
        리뷰어에게 어떤점을 어필하고 싶은지가 명확하지 않습니다.
        예상되는 어필 포인트는.
        1. redis 사용 경험
		2. thread 사용 경험
		3. stopwatch 를 이용한 퍼포먼스 체크 경험.
		정도로 보이는데. thread 사용 경험 부분은 크게 어필 되지 않는다는것이 제 의견입니다.
		어떤 인상을 남기고 싶은지를 설정하셨고. 목적에 부합했는지를 체크 해보셨으면 합니다.
		코드로는 전달이 어려울 수 있으니. 아예 코드에 주석으로 설명 하시는것도 좋은 방법입니다.
         */

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