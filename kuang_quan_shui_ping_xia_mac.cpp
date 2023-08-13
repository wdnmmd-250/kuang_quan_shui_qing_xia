//作者 fx 
//86+13366532090 联系我们+发送反馈

//WASD移动
//Z投掷矿泉水瓶 
//G短距离水弹
//C c_lv阶限制 高阶水涡 

//v 0.0.3
 


#include<iostream>
#include<unistd.h>
#include<time.h>
using namespace std;

int c_lv=2;
char line[5][150];
int wt=100,ht=5; 
char player='G';


char get_key(){
  system("stty raw");
  char key=getchar();
  system("stty cooked");
  return key;
}

bool up_rim(int y){
	return y>0;
}
bool down_rim(int y){
	return y<ht-1;
}
bool left_rim(int x){
	return x>0;
}
bool right_rim(int x){
	return x<wt-1;
}
int wave(char a){
	return (a=='>')*2+(a=='<')*4+(a=='A')*3+(a=='v');
}
int main(){
	srand(time(0));
	
	int player_x=rand()%wt,player_y=rand()%ht;
	double lanch_lim=3,hp=3;
	int exp=0,cilp=3,lv=0;
	int f_time=3;
	double reload=0.1;
	int foe_num=0,foe_lim=3; //限制敌人数 
	 //初始化道路
	for(int i=0;i<ht;i++){
		for(int j=0;j<wt;j++){
			line[i][j]='-';
		}
	}
	
	time_t begin=clock(); //用于计时 
	
	while(1)
	{
		if(player=='F'){
			f_time-=1;
		}if(f_time==0){
			player='G';
		}
		system("clear");
		string tmp_space;
		for(int i=0;i<wt-35;i++){
			tmp_space+=' ';
		}cout<<tmp_space;
		printf("-----广告位招租-----\n"); 
		printf("水瓶：%f",lanch_lim);
		printf("  血量：%f",hp);
		cout<<tmp_space;
		printf("击杀数：%d",exp);
		printf("\n\n\n\n\n");//留出空间，5比较吉利 
		 
		//渲染 
		//种树 
		for(int i=0;i<wt;i++){
			if(i%2==0)
				printf("T");
			else{
				printf(" ");
			}
			
		}printf("\n");
		for(int i=0;i<ht;i++){
			printf("|");
			for(int j=0;j<wt;j++){
				if(i==player_y&&j==player_x) cout<<player;
				else printf("%c",line[i][j]);
			}printf("P\n");
		}
		for(int i=0;i<wt;i++){
			if(i%2==1)
				printf("T");
			else{
				printf(" ");
			}
			
		}
		char key=get_key();//读取按键 
		

		
		
		//玩家
		
		//玩家移动
		if(key>='A'&&key<='Z'){
			key+='a'-'A';
		}
		if(lanch_lim<cilp){
			lanch_lim+=reload;
		}
		if(lanch_lim>cilp){
			lanch_lim=cilp;
		}
		if(key=='z'){
			if(lanch_lim>=1){
				line[player_y][player_x-1]='(';
				lanch_lim--;
			}
		}else if(key=='g'){
			if(lanch_lim>=0.6){
				line[player_y][player_x-1]='w';
				lanch_lim-=0.6;
			}
		}else if(key=='f'){
			if(lanch_lim>=0.9){
				player='F';
				f_time=3; 
				lanch_lim-=0.9;
			}
		}else if(key=='c'&&lv>c_lv){
			if(lanch_lim>=3){
				line[player_y][player_x-1]='<';
				lanch_lim-=3;
			}
		}else if(key=='a'&&left_rim(player_x)){
			player_x-=1;
		}else if(key=='s'&&down_rim(player_y)){
			player_y+=1;
		}else if(key=='d'&&right_rim(player_x)){
			player_x+=1;
		}else if(key=='w'&&up_rim(player_y)){
			player_y-=1;
		}
		
		
		//判定死亡 
		if(hp<=0){
			time_t end=clock();
			double tm=(end-begin)/1000.0;
			int j=0;
			while(1){
			system("cls");
				cout<<"\\----\\\\  ----   /\\\\   \\----\\\\ \n";
				cout<<"|   ||  ||---  /__\\\\  |   ||  \n";
				cout<<"|___//  ||___ /    \\\\ |___//  \n";
				cout<<"GAME OVER";
				for(int i=0;i<j+1;i++){
					cout<<'.';
				}j++;
				j%=3;
				cout<<"\n总结：\n";
				cout<<"H============\n";
				cout<<"| "<<"击杀数："<<exp<<'\n';
				cout<<"| "<<"等级：  "<<lv<<'\n';
				cout<<"| "<<"用时:   "<<tm<<"秒"<<'\n';
				cout<<"H============" ;
				usleep(999999);
			}
			
		} 
		
		//玩家进化
		if(exp%3==0&&lv!=exp/3){
			hp+=1;
			cilp+=1;
			lv=exp/3;
		}
		
		
		
		//关卡机制
		
		foe_lim=3+lv;
		
		if(reload<=exp/50.0+0.1&&exp%5==0){
			reload+=0.03;
		}

		
		
		//敌人
		
		
		if(rand()%3==1&&foe_num<foe_lim){
			line[rand()%3][0]=rand()%9+'1';
			foe_num++;
		} 
		
		for(int i=0;i<ht;i++){
			for(int j=0;j<wt;j++){
				if(line[i][j]>'0'&&line[i][j]<='9'){
					
					//敌人 机制
					
					int x=j,y=i; //移动后位置 
					if(rand()%2==1||line[i][j]=='4'){
						if(rand()%(5+(line[i][j]=='4'))>2){
								//最优路线 
								if(player_x>x){
									x++;
								}
								if(player_x<x){
									x--;
								}
								if(player_y>y){
									y++;
								}
								if(player_y<y){
									y--;
								}
						}else{
							x+=rand()%3-1;
							y+=rand()%3-1;
							if(x<0){
								x++;
							}if(x>=wt){
								x--;
							}if(y<0){
								y++;
							}if(y>=ht){
								y--;
							}
							if(x<10){
								x=abs(x);
								x++;
							}
						}
					}
					
					
					//碰撞
						//受伤
						if(line[i][j+1]=='('){
							line[i][j+1]='-';
							line[i][j]-=1;
						}
						if(line[i][j+1]=='O'||line[i][j+1]=='o'||line[i][j+1]=='.'){
							line[i][j]-=1;
						}
						int ranges=2;
						for(int n=-ranges;n<=ranges;n++){
							for(int m=-ranges;m<=ranges;m++)
								if(wave(line[i+n][j+m])){
									x=j;
									y=i;
									line[i][j]-=wave(line[i+n][j+m]);
									break;
								}
						}
						
					//攻击
					if(y==player_y&&(x==player_x||x+1==player_x)){
						if(player=='F'){
							line[i][j]-=2;
						}
						hp-=1;
						x-=1;
					}
					
					if(line[i][j]>='5'&&rand()%15==1){
						line[i][j+1]='#';
					}
					
				//死亡
					if(line[i][j]<='0'){
						
						line[i][j]='-';
						foe_num--;
						exp++;
						hp+=0.5;
					}else{
						line[i][j]-='9'+1;
					}
					swap(line[i][j],line[y][x]);
					
					
				
				}
			}
		}
		foe_num=0;
		for(int i=0;i<ht;i++){
			for(int j=0;j<wt;j++){
				char raw=line[i][j]+'9'+1;
				if(raw>'0'&&raw<='9'){
					foe_num++;
					line[i][j]=raw;
				} 
			}
		}
				
				
		//更新子弹
		
		for(int i=0;i<ht;i++){
			for(int j=0;j<wt;j++){
				if(line[i][j]=='('){
						line[i][j]=')';
						int m=1;
						while(line[i][j-m]=='('){ //防止出现：<< >< >> << 
							m++; 
						}
						if(j-m>0)
							swap(line[i][j],line[i][j-m]);
						else{
							line[i][j]='-';
						}

				}
			}
		}
		for(int i=0;i<ht;i++){
			for(int j=0;j<wt;j++){
				if(line[i][j]==')'){
					line[i][j]='(';
				}
				if(line[i][j]=='.'){
					line[i][j]='-';
				}
				if(line[i][j]=='w'){
					line[i][j]='O';
					swap(line[i][j],line[i][j-1]);
				}
				if(line[i][j]=='o'){
					line[i][j]='.';
					swap(line[i][j],line[i][j-1]);
				}
				if(line[i][j]=='O'){
					line[i][j]='o';
					swap(line[i][j],line[i][j-1]);
				}
				if(line[i][j]=='v'){
					line[i][j]='O';
				}
				if(line[i][j]=='>'){
					line[i][j]='v';
				}
				if(line[i][j]=='A'){
					line[i][j]='>';
				}
				if(line[i][j]=='<'){
					line[i][j]='A';
				}
				if(line[i][j]=='#'){
					line[i][j]='*';
					int m=1;
					while(line[i][j+m]=='#'){ //防止出现：<< >< >> << 
							m++; 
						}
						if(j+m<wt-1)
							swap(line[i][j],line[i][j+m]);
						if(j==wt-1)
							line[i][j]='-';
						
				}
				if(line[i][j]=='*'){
					line[i][j]='#';
				}  
				
			}
		}

		//玩家接收子弹
		if(line[player_y][player_x-1]=='#'){
			line[player_y][player_x-1]='-';
			hp-=0.5;
		} 
		
		
		

	}
	
}
