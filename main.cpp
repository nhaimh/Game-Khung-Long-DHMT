#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int n = 2;
float vatCan[1000][3];
int diem = 0;
float height = 0.15, width = 0.08;
float yNV = -0.5;

float VVatCan = 0.03;
bool start = false;
bool start1 = false ; 
bool start2 = false ; 

bool lose = false;

float maxNhay = 0.3 ; 
int countNhay = 0 ; 

void khoiTaoVatCan(){

	for (int i = 0; i < n; i++)
		vatCan[i][0] = 2- width;
	for (int i = 0; i < n; i++){
		int k = rand() % 2;
		if (k == 0){
			vatCan[i][1] = -0.2;
			vatCan[i][2] = 0.08;
		}else{
			vatCan[i][1] = -0.5;
			if (rand() % 2)
				vatCan[i][2] = 0.18;
			else
				vatCan[i][2] = 0.25;
		
		}
	}			
}

void diemCao(){

	glColor3f(1.0, 1.0, 0.0); 
	glRasterPos2f(0, 0.80); 
	
	ostringstream convert;   
    convert << diem;      
    string result = convert.str(); 
	string s = "Diem: " + result ; 
	if (!lose)
		diem++;

	char * charkq = new char [s.length()+1];  
	strcpy (charkq, s.c_str()); 
	
	for (int i = 0 ; i < strlen(charkq); i ++) { 
	    char c = s[i]; 
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); 
	}
	
	if(lose){
		glColor3f(1.0, 1.0, 0.0);
		glRasterPos2f(0, 0.70); 
		string thua = "Ban da thua";
		char * charThua = new char [thua.length()+1];
		strcpy (charThua, thua.c_str());
	
		for (int i = 0 ; i < strlen(charThua); i ++) { 
	    	char c = charThua[i]; 
	    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); 
		}	
	
	}


}


void veDuong(){
	glBegin(GL_LINES);
 	glVertex3f(-600.0, -0.5, 0.0);
 	glVertex3f(600.0, -0.5, 0.0);
 	glEnd();
 
}

void nhay(){
	if (!lose){
		if(start == true && start1 == false){
			yNV += 0.03;
			if(yNV >= maxNhay)
				start1 = true; 
		}else if(start == true && start1 == true){
			if(start2 == true)
				yNV -= 0.02; 
			yNV -= 0.03;
			if(yNV <= -0.5){
				start = false;
				start1 = false; 
				start2 = false; 
				yNV = -0.5; 
				maxNhay = 0.3; 
				countNhay = 0 ;
			}
		}
		
		
	}
}

void ve(float a, float b, float c){
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON); 
		glVertex2f (a, b); 
		glVertex2f (a + width, b);
		glVertex2f (a + width, b + c);
		glVertex2f (a, b + c);
	glEnd();
}

void veVatCan(){

	for (int i = 0; i < n; i++)
		ve(vatCan[i][0], vatCan[i][1], vatCan[i][2]);
	
	for (int i = 0; i < n; i++)
		if(diem < 200)
			vatCan[i][0] -=  VVatCan;
		else if(diem >= 200 && diem < 400){
			if(!lose){
				vatCan[i][0] -=  (VVatCan + 0.02); 
			}
				
		}
				
		else if(diem >= 400 && diem < 700) {
			if(!lose){
					vatCan[i][0] -=  (VVatCan + 0.03);	
			}
		
		}else {
			if(!lose){
					vatCan[i][0] -=  (VVatCan + 0.04);	
			}
		}
			
	for (int i = 0; i < n; i++){
		if (vatCan[i][0] >= -1 - width && vatCan[i][0] <= -1 + width){

			if ((yNV >= vatCan[i][1] && yNV <= (vatCan[i][1] + vatCan[i][2])) || (yNV + height >= vatCan[i][1] && yNV + height <= vatCan[i][1] + vatCan[i][2])){
				VVatCan = 0;
				lose = true;
			}
		}
	}
	bool kt = true;
	for (int i = 0; i < n; i++)
		if (vatCan[i][0] > -2){
			kt = false;
			break;
		}
	if (kt)
		khoiTaoVatCan();
		 
}
void veKhungLong(float y){
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON); 
		glVertex2f (-1, y); 
		glVertex2f (-1, y + height);
		glVertex2f (width - 1, y + height);
		glVertex2f (width - 1, y);
	glEnd();
}

void khungLong(){
	veKhungLong(yNV);
	veVatCan();
	veDuong();
	diemCao();
	if (start)
		nhay();
}

void sleep(int i){
	for(int time = 0 ; time < i ;time++){
		for(int count = 0 ; count < 2200000 ; count++);
	}
}
void updateScreen(void){
	glutPostRedisplay();
	glFlush();
	glClear(GL_COLOR_BUFFER_BIT);
	sleep(5);
}
void mydisplay(){
	khungLong();
	updateScreen();
}

void MouseButton(int type_button, int state, int x, int y)
{
 if (type_button == GLUT_LEFT_BUTTON)
 {
  if (state == GLUT_UP)
  {
 		if(yNV == -0.5)
		  	start = true;
		else{
			maxNhay = 0.8 ; 
			start1 = false ; 
		}
		glutPostRedisplay();
  }
 }else{
 }
}

void keynhay(int key, int x, int y){
	if(key == GLUT_KEY_UP  ){
		if(yNV == -0.5){
		  	start = true;
		  	countNhay = 1 ;
		}else if(countNhay == 1) {
			maxNhay = 0.6 ; 
			start1 = false ; 
			countNhay = 2; 
		}
	}else if(key == GLUT_KEY_DOWN && yNV != -0.5){
		start1 = true; 
		start2 = true; 
		
	}
 	glutPostRedisplay();
}
 
int main(int argc, char** argv){
	srand(time(NULL));
	khoiTaoVatCan();
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1200, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Game khung long");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho(-2, 2, -1, 1, -1, 1);

	glutDisplayFunc(mydisplay);
	glutSpecialFunc(keynhay);
	glutMouseFunc(MouseButton) ;
	glutMainLoop();  
}
