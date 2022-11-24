// main.c     main 코드(C로 해야함) 임시 프로토타입
#include <stdio.h>
#include <ncurses.h> 
   
#include "filefunc.h" // 제가 만든 함수포함된 헤더파일
   
int main(){
   
     // 이 부분은 로그인창 화면, 사용자들이 본인 이름들 입력
  
    char userid1[30]="player1";
    char userid2[30]="player2"; // 로그인창으로 부터 유저 이름을 각각 받아왔다고 가정,  실제로는 로그인 화면 팀의 함수에서 이름이 반환된다던지 하는 식으로 char에 각각 저장됨
  
    userfilecreate(userid1);
    userfilecreate(userid2); // 각각의 플레이어들의 이름으로 된 data파일을 생성함, 로그인 후, 항상 호출되게 해야하고, 두번째 로그인부터는 함수가 별 동작없이 넘어감
 
 
     //--------------------- 이부분은 실제 오목 게임부분
  
     //게임이 끝남
  
     //이제 게임구현팀에서 각 플레이어들의 승패값을 int 형 으로 받아와야함 (이겼으면 1, 졌으면 0)
 
    int result1=0;  //player1의 방금 게임 결과, 패배했음으로 0 받아왔다고 가정
    int result2=1; // 같이 플레이한 player2는 당연히 이김, 1받아왔다고 가정
  
    userfilesave(userid1,userid2,result1,result2); //게임이 끝난 후 항상 호출되게 해야함, 로그인할 때 만들어 놓은 각각의 유저 데이터파일에 승패값을 받아서 승,패,점수 값 업데이트
  
    return 0;
 
}
