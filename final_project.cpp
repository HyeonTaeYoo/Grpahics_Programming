#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include "ObjParser.h"
#include "bmpfuncs.h"

using namespace std;

#define pi 3.1415926535897
double radian = pi / 180;
double radius = 2;

double theta = 80 * radian, phi = 45 * radian;
double r = 50;
double X = r * sin(theta) * cos(phi);
double Y = r * sin(theta) * sin(phi);
double Z = r * cos(theta);

using std::cos;
using std::sin;
using std::sqrt;

// global variable for counting fps
volatile int frame = 0, time, timebase = 0;
volatile float fps;

/* texture mapping set variable */

GLuint texture_dron;
GLuint Env[6]; //환경맵1
GLuint Env2[6]; //환경맵2
GLuint Env3[6]; //환경맵3
GLuint Env4[6]; //환경맵4

GLuint texName2[6]; // 박스 매핑용

GLuint g_nCubeTex;
GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;

int capture = 0;
int current_width;
int current_height;
int modelselect = 1;
int cnt = 0;

float m_RotateAngle=0;
float take_off=0;
float right_left = 0;
float front_back=0;
float seperate_speed = 0; 
float temp1, temp2, temp3;
float object_rot = 0;
float tempa, tempb =0;
float drop;

bool axis = false;
bool speed_up = false;
bool speed_down = false;
bool front, back, lt, rt , rst = false;
bool sight_camera, sep_sw = false;
bool seperate = false;
bool environ_map = true;
bool environ_map_sight = true;
bool color_selection = false;

// object var
ObjParser* monkey;
ObjParser* dron1;
ObjParser* dron2;
ObjParser* dron3;
ObjParser* dron4;
ObjParser* dron5;
ObjParser* dron6;
ObjParser* dron7;
ObjParser* dron8;
ObjParser* dron9;
ObjParser* dron10;
ObjParser* dron11;
ObjParser* dron12;
ObjParser* dron13;
ObjParser* dron14;
ObjParser* dron15;
ObjParser* dron16;
ObjParser* dron17;
ObjParser* dron18;
ObjParser* dron19;
ObjParser* dron20;
ObjParser* dron21;

// user-defined function
void init(void);
void light_default();
void add_menu();
void mouse(int, int, int, int);
void mouseWheel(int, int, int, int);
void motion(int, int);
void passiveMotion(int, int);
void keyboard(unsigned char, int, int);
void special_keyboard(int, int, int);
void idle(void);
void draw(void);
void resize(int, int);

void draw_skybox(float size);
void keyboard_navigation();
void setTextureMapping();
void draw_obj(ObjParser*);
void draw_cube_textures();
void draw_textureCube();
void draw_Environment(float size);
void draw_Environment2(float size);
void draw_Environment3(float size);
void draw_Environment4(float size);
void Environment_Mapping();
void Environment_Mapping2();
void Environment_Mapping3();
void Environment_Mapping4();

void draw_axis(void);
void draw_obj_with_texture(ObjParser*);
void draw_obj_with_texture2(ObjParser*);
void draw_obj_with_texture3(ObjParser*);
void draw_obj_with_texture4(ObjParser*);
void draw_obj_with_texture5(ObjParser*);
void draw_texture_Cube2(float );
void cubeTextureMapping2();
void draw_object();
void draw_camera_sight();
void draw_string(void*, const char*, float, float, float, float, float, float);
void draw_string_switch();
void draw_text();
void draw_string_switch2();

void get_resource1(const char* str);
void get_resource2(const char* str);
void get_resource3(const char* str);
void get_resource4(const char* str);
void get_resource5(const char* str);
void get_resource6(const char* str);
void get_resource7(const char* str);
void get_resource8(const char* str);
void get_resource9(const char* str);
void get_resource10(const char* str);
void get_resource11(const char* str);
void get_resource12(const char* str);
void get_resource13(const char* str);
void get_resource14(const char* str);
void get_resource15(const char* str);
void get_resource16(const char* str);
void get_resource17(const char* str);
void get_resource18(const char* str);
void get_resource19(const char* str);
void get_resource20(const char* str);
void get_resource21(const char* str);

void keyboard_navigation() {
	printf("===========Keyboard Manual=============\n");
	printf(" 방향키   : 시점변화\n");
	printf(" w/a/s/d  : Moving Delivery Drone\n");
	printf(" f        : Capture the Box \n");
	printf(" ESC: Quit the program\n");
	printf(" t        : Take off\n");
	printf(" l        : Landing\n");
	printf(" g        : Action Stop\n");
	printf(" x        : Disassemble/Assemble Parts\n");
	printf(" c        : Change the Sight (<-> drone's camera) \n");
	printf(" m        : Mini Map On/Off\n");
	printf(" n        : Envrionment On/Off\n");
	printf(" i         : Axis On/Off\n");
	printf(" q/e     : Rotate Delivery Drone\n");
	printf("==========================================\n");

}


/* Main method */
int main(int argc, char** argv)
{
	// glut initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1600, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("12161754 유현태 GL Program");

	// 사용자 초기화 함수
	init();
	// 키보드 네비게이션 출력
	keyboard_navigation();
	// pop-up 메뉴 등록 함수
	add_menu();

	// 리소스 로드 함수
	get_resource1("./obj_new/back_left_arm.obj");
	get_resource2("./obj_new/back_left_wing.obj");
	get_resource3("./obj_new/back_right_arm.obj");
	get_resource4("./obj_new/back_right_wing.obj");
	get_resource5("./obj_new/body_front.obj");
	get_resource6("./obj_new/front_left_arm.obj");
	get_resource7("./obj_new/front_left_wing.obj");
	get_resource8("./obj_new/front_right_arm.obj");
	get_resource9("./obj_new/front_right_wing.obj");
	get_resource10("./obj_new/dron_camera.obj");
	get_resource11("./obj_new/dron_camera_connect.obj");
	get_resource12("./obj_new/front_right_pick.obj");
	get_resource13("./obj_new/front_left_pick.obj");
	get_resource14("./obj_new/back_right_pick.obj");
	get_resource15("./obj_new/back_left_pick.obj");
	get_resource16("./obj_new/battery.obj");
	get_resource17("./obj_new/battery_holder.obj");
	get_resource18("./obj_new/body_middle.obj");
	get_resource19("./obj_new/body_back.obj");
	get_resource20("./obj_new/body_middle_base.obj");
	get_resource21("./obj_new/body_middle_color.obj");
	/* Create a single window with a keyboard and display callback */
	glutMouseFunc(&mouse);
	glutMouseWheelFunc(&mouseWheel);
	glutMotionFunc(&motion);
	glutPassiveMotionFunc(&passiveMotion);
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(&special_keyboard);

	glutDisplayFunc(&draw);
	glutIdleFunc(idle);
	glutReshapeFunc(&resize);

	//glutIdleFunc(&idle);

	/* Run the GLUT event loop */
	glutMainLoop();

	return EXIT_SUCCESS;
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	//glDisable(GL_LIGHT1);
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	draw_string_switch();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();


	glPopMatrix();
	draw_object();

	glPopMatrix();
	draw_camera_sight();

	glPopMatrix();
	draw_text();
	glFlush();
	glutSwapBuffers();
}

void draw_text()
{
	glViewport(0, current_height / 2, current_width / 2, current_height / 2);
	glLoadIdentity();

	draw_string(GLUT_BITMAP_HELVETICA_18, "Keyboard Manual", -9, 7, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "w/a/s/d  : Moving Delivery Drone", -9, 6, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "f        : Capture the Box", -9, 5, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "t        : Take off", -9, 4, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "l        : Landing", -9, 3, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "g        : Action Stop", -9, 2, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "x        : Disassemble/Assemble Parts", -9, 1, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "c        : Change the Sight (<-> drone's camera)", -9, 0, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "m        : Mini Map On/Off", -9, -1, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "n        : Envrionment On/Off", -9, -2, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "i         : Axis On/Off", -9, -3, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "q/e     : Rotate Delivery Drone", -9, -4, 5, 1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "Direction key: Change the Sight", -9, -5, 5, 1, 1, 1);
	draw_string_switch();
	glFlush();
}
void draw_camera_sight()
{
	glViewport(current_width *4/ 5, current_height * 4 / 5, current_width / 4, current_height / 4);
	gluLookAt(right_left, -1 + take_off, -4 + front_back, right_left, take_off, front_back - 600, 0, 1, 0);// 카메라로 시점 변경하기 


	//이동 제어 코드
	if (speed_up == true) {
		m_RotateAngle = m_RotateAngle + 100;
		take_off += 0.1;
		if (take_off >= 10) take_off -= 0.1;
	}
	else if (speed_down == true) {
		m_RotateAngle += 1;
		take_off -= 0.1;
		if (take_off <= 0.1) take_off += 0.1;
	}
	else m_RotateAngle = 0;

	if (m_RotateAngle > 360) m_RotateAngle -= 360;

	if (front == true) front_back -= 0.05;
	if (back == true) front_back += 0.05;
	if (rt == true) right_left -= 0.05;
	if (lt == true) right_left += 0.05;


	glPushMatrix();
	glPushMatrix();
	glPopMatrix();

	if (environ_map_sight) {
		glTranslatef(0, 50, 0);
		if (modelselect == 1) draw_Environment(100);
		else if (modelselect == 2) draw_Environment2(100);
		else if (modelselect == 3) draw_Environment3(100);
		else if (modelselect == 4) draw_Environment4(100);
	}
	glPopMatrix();
	glTranslatef(right_left, take_off, front_back);


	glFlush();
}
void draw_object()
{

	glViewport(0, 0, current_width , current_height );

	draw_string_switch2();
	if (sight_camera == true) {
	
		gluLookAt(right_left, -1 + take_off, -4 + front_back, right_left, take_off, front_back - 600, 0, 1, 0);// 카메라로 시점 변경하기 
	}
	else if (sight_camera == false) {
		if (theta <= pi) gluLookAt(X, Z, Y, 0, 0, 0, 0, 1, 0);
		else if (theta > pi) gluLookAt(X, Z, Y, 0, 0, 0, 0, -1, 0);
	}

	//이동 제어 코드
	if (speed_up == true) {
		m_RotateAngle = m_RotateAngle + 150;
		take_off += 0.1;
		if (take_off >= 15) take_off -= 0.1;
	}
	else if (speed_down == true) {
		m_RotateAngle += 1;
		take_off -= 0.1;
		if (take_off <= 0.1) take_off += 0.1;
	}
	else m_RotateAngle = 0;

	if (m_RotateAngle > 360) m_RotateAngle -= 360;

	if (front == true) front_back -= 0.05;
	if (back == true) front_back += 0.05;
	if (rt == true) right_left -= 0.05; 
	if (lt == true) right_left += 0.05;
	if (capture % 2 == 0 && capture > 1&&temp2 > 4) drop += 0.2;
	if (11 -drop <0.001) drop = 0, temp2 =4;
	if(axis) draw_axis();


	glPushMatrix();
	glPushMatrix();
	glPopMatrix();

	if (environ_map) {
		glTranslatef(0, 50, 0);

		if(modelselect==1) draw_Environment(100);
		else if (modelselect == 2) draw_Environment2(100);
		else if (modelselect == 3) draw_Environment3(100);
		else if (modelselect == 4) draw_Environment4(100);
	}
	glPopMatrix();

	glPushMatrix();

	if (capture == 0) {
		glTranslatef(15, 0, 0);
		draw_texture_Cube2(2);
	}
	if (capture % 2 == 0 && capture > 1) {
		glTranslatef(temp1, temp2 - 4, temp3 + 1.5); //배달드론 보다 살작 아래에 잡고 있는거 구현
		if (temp2 > 4) {
				glTranslatef(0, -drop, 0);
		}
		draw_texture_Cube2(2);
	}
	glPopMatrix();
	//이동 	

	glTranslatef(right_left, take_off, front_back);
	tempa = right_left;
	tempb = front_back;
	glTranslatef(-tempa, 0, -tempb);
	glRotatef(object_rot, 0, 1, 0);
	glTranslatef(tempa, 0, tempb);

	//if (rt) {
	//	glTranslatef(right_left, take_off, front_back);
	//	glRotatef(30, 0, 0, 1);
	//	glTranslatef(-right_left, -take_off, -front_back);
	//}
	//if (lt) {
	//	glTranslatef(right_left, take_off, front_back);
	//	glRotatef(-30, 0, 0, 1);
	//	glTranslatef(-right_left, -take_off, -front_back);
	//}

	GLfloat spot_direction[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);


	glPushMatrix();
	glPushMatrix();


	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();


	glPopMatrix();
	if (capture %2 ==1) {
		glTranslatef(0, -4, 1.5);
		draw_texture_Cube2(2);
		temp1 = right_left;
		temp2 = take_off;
		temp3 = front_back;
	}



	glPopMatrix();
	glColor3f(1.f, 1.f, 1.f);

	if (sep_sw == true)	glTranslatef(-seperate_speed, 0, 0);
	draw_obj_with_texture2(dron1); // back_left_arm

	glPopMatrix();

	if (sep_sw == true)	glTranslatef(0, seperate_speed, 0);
	glTranslatef(-7.0625, 0, 6.3422);
	glRotatef(m_RotateAngle, 0, 1, 0);
	glTranslatef(7.0625, 0, -6.3422);
	draw_obj_with_texture(dron2); // back_left_wing

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(seperate_speed, 0, 0);
	draw_obj_with_texture2(dron3); // back_right_arm

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, seperate_speed, 0);
	glTranslatef(7.1422, 0, 6.3422);
	glRotatef(m_RotateAngle, 0, 1, 0);
	glTranslatef(-7.1422, 0, -6.3422);
	draw_obj_with_texture(dron4); // back_right_wing



	glPopMatrix();

	if (sep_sw == true)	glTranslatef(0, 0, -seperate_speed);
	draw_obj_with_texture2(dron5); //body front


	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, 2*seperate_speed, 0);
	draw_obj_with_texture3(dron18); //body middle

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, 2*seperate_speed, 0);
	if(color_selection)	draw_obj_with_texture4(dron21); //body middle_color
	else draw_obj_with_texture5(dron21);

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, 0);
	draw_obj_with_texture2(dron20); //body middle_base

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, seperate_speed, seperate_speed);
	draw_obj_with_texture2(dron19); //body back

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, 1.8* seperate_speed, seperate_speed);
	draw_obj_with_texture2(dron16); //battery

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, 1.5* seperate_speed, seperate_speed);
	draw_obj_with_texture(dron17); //battery_holder


	glPopMatrix();
	if (sep_sw == true)	glTranslatef(-seperate_speed, 0, 0);
	draw_obj_with_texture2(dron6); //front_left_arm

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(seperate_speed, 0, 0);
	draw_obj_with_texture2(dron8); //front_right_arm

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, seperate_speed, 0);
	glTranslatef(-6.6537, 0, -4.4701);
	glRotatef(m_RotateAngle, 0, 1, 0); 
	glTranslatef(6.6537, 0, 4.4701);
	draw_obj_with_texture(dron7); // front_left_wing


	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, seperate_speed, 0);
	glTranslatef(6.7311, 0, -4.5017);
	glRotatef(m_RotateAngle, 0, 1, 0);
	glTranslatef(-6.7311, 0, 4.5017);
	draw_obj_with_texture(dron9); // front_right_wing


	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, -seperate_speed);
	draw_obj_with_texture3(dron10); //("./obj_new/dron_camera.obj");

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, 0, -seperate_speed);
	draw_obj_with_texture2(dron11); ///obj_new/dron_camera_connect.obj");

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, -seperate_speed);
	draw_obj_with_texture2(dron12); ///obj_new/front_right_pick.obj");

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, -seperate_speed);
	draw_obj_with_texture2(dron13); ///obj_new/front_left_pick.obj");

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, seperate_speed);
	draw_obj_with_texture2(dron14); ///obj_new/back_right_pick.obj");

	glPopMatrix();
	if (sep_sw == true)	glTranslatef(0, -seperate_speed, seperate_speed);
	draw_obj_with_texture2(dron15); ///obj_new/back_left_pick.obj");


	glFlush();
}

void light_default() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	/* Light0 조명 관련 설정 */
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.9f, 1.0f };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/* Light1 조명 관련 설정 */
	GLfloat ambientLight1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_position1[] = { 0.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

	/********* light point position setting **********/
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	/************* spot position setting *************/

	GLfloat specularMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	/************* Material  setting *************/
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);


	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* DEPTH TEST ENABLE */
	glFrontFace(GL_CW);	// CW CCW바꿔보면서 front face 변경해보기!
}



void init()
{
	printf("init func called\n");
	// clear background color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// set blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// set antialiasing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_LINE_SMOOTH);

	light_default();
	/* TEXTURE MAPPING SET */
	Environment_Mapping();
	Environment_Mapping2();
	Environment_Mapping3();
	Environment_Mapping4();

	cubeTextureMapping2();
	glEnable(GL_TEXTURE_2D);
	setTextureMapping();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_REPLACE : polygon의 원래 색상은 무시하고 texture로 덮음
}

void special_keyboard(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_LEFT:
		phi -= 5 * radian;
		if (phi < 0) {
			phi += 2 * pi;
		}
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		break;

	case GLUT_KEY_RIGHT:
		phi += 5 * radian;
		if (phi > 2 * pi) {
			phi -= 2 * pi;
		}
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		break;
	case GLUT_KEY_UP:
		theta += 5 * radian;
		if (theta > 2 * pi) {
			theta -= 2 * pi;
		}
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		break;
	case GLUT_KEY_DOWN:
		theta -= 5 * radian;
		if (theta < 0) {
			theta += 2 * pi;
		}
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		
		break;
	case GLUT_KEY_PAGE_UP:
		r -= radius;
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		
		break;
	case GLUT_KEY_PAGE_DOWN:
		r += radius;
		X = r * sin(theta) * cos(phi);
		Y = r * sin(theta) * sin(phi);
		Z = r * cos(theta);
		
		break;

	}
	glutPostRedisplay();
}
/* Keyboard callback function */

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
			/* Exit on escape key press */
		case '\x1B':
		{
			exit(EXIT_SUCCESS);
			break;
		}
		case 'i':
		{
			axis = !axis;
			break;
		}
		case 'y':
		{
			speed_down = !speed_down;
			speed_up = false;
			break;
		}
		case 't':
		{
			speed_up = !speed_up;
			speed_down = false;
			break;
		}
		case 's':
		{
			back = !back;
			front = false;
			lt = false;
			rt = false;
			break;
		}
		case 'w':
		{
			front = !front;
			back = false;
			lt = false;
			rt = false;
			break;
		}
		case 'a':
		{
			rt = !rt;
			lt = false;
			back = false;
			front = false;
			break;
		}

		case 'd':
		{
			lt = !lt;
			rt = false;
			back = false;
			front = false;
			break;
		}
		case 'q':
		{
			object_rot += 2;
			break;
		}
		case 'e':
		{
			object_rot -= 2;
			break;
		}
		case 'g':
		{
			lt = false;
			rt = false;
			back = false;
			front = false;
			speed_up = false;
			speed_down = false;
			break;
		}
		case 'c':
		{
			sight_camera = !sight_camera;
			break;
		}
		case 'x':
		{
			seperate = !seperate;
			sep_sw = true;
			break;
		}
		case 'f':
		{
			capture +=1;
			if (capture == 50)capture = 0;
			break;
		}
		case 'm':
		{
			environ_map_sight = !environ_map_sight;
			break;
		}
		case 'n':
		{
			environ_map = !environ_map;
	
			break;
		}
	}
	glutPostRedisplay();
}
void draw_axis(void)
{
	glLineWidth(1.5f);
	glBegin(GL_LINES);

	glColor4f(1.f, 0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(14.f, 0.f, 0.f);

	glColor4f(0.f, 1.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 14.f, 0.f);

	glColor4f(0.f, 0.f, 1.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 14.f);

	glEnd();
	glLineWidth(1);
}

void draw_obj(ObjParser* objParser)
{
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

void draw_obj_with_texture(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}
void draw_obj_with_texture4(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}
void draw_obj_with_texture5(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture5);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}
void draw_obj_with_texture2(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}
void draw_obj_with_texture3(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture3);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}

//환경맵 용 박스
void Environment_Mapping() {
	glGenTextures(6, Env);
	int imgWidth, imgHeight, channels;

	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, Env[i]);
		char buf[100];

		sprintf(buf, "img/img/r%d.bmp", i);


		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

		//X = r * sin(theta) * cos(phi);
		//Y = r * sin(theta) * sin(phi);
		//Z = r * cos(theta);
		//glLoadIdentity();
	}
} 

void Environment_Mapping2() {
	glGenTextures(6, Env2);
	int imgWidth, imgHeight, channels;

	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, Env2[i]);
		char buf[100];

		sprintf(buf, "img/img/t%d.bmp", i);


		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

		//X = r * sin(theta) * cos(phi);
		//Y = r * sin(theta) * sin(phi);
		//Z = r * cos(theta);
		//glLoadIdentity();
	}
}

void Environment_Mapping3() {
	glGenTextures(6, Env3);
	int imgWidth, imgHeight, channels;

	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, Env3[i]);
		char buf[100];

		sprintf(buf, "img/img/o%d.bmp", i);


		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	}
}

void Environment_Mapping4() {
	glGenTextures(6, Env4);
	int imgWidth, imgHeight, channels;

	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, Env4[i]);
		char buf[100];

		sprintf(buf, "img/img/p%d.bmp", i);


		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	}
}



void draw_Environment(float size) {
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);

	//Quad 1
	glBindTexture(GL_TEXTURE_2D, Env[0]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size , size);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();
	//Quad 2

	glBindTexture(GL_TEXTURE_2D, Env[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size , -size);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glEnd();

	//Quad 3
	glBindTexture(GL_TEXTURE_2D, Env[2]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size , -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glEnd();

	//Quad 4
	glBindTexture(GL_TEXTURE_2D, Env[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size , size);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glEnd();

	//Quad 5
	glBindTexture(GL_TEXTURE_2D, Env[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();

	//Quad 6
	glBindTexture(GL_TEXTURE_2D, Env[5]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size , size);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size , -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size , -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, -size , size);   //V1
	glEnd();

} 
void draw_Environment2(float size) {
	glColor3f(1.0, 1.0, 1.0); // white로 color를 set 해주어야 texture 색상이 제대로 적용됨
	////glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_MODULATE를 하면 원래 텍스쳐랑
	//// 폴리건의 원래 색깔이랑 곱혀져서 덮음, 텍스쳐가 입혀진 표면에 광원 효과 설정도 가능해진다.
	////glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glDisable(GL_LIGHTING);

	//Quad 1
	glBindTexture(GL_TEXTURE_2D, Env2[0]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();
	//Quad 2

	glBindTexture(GL_TEXTURE_2D, Env2[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glEnd();

	//Quad 3
	glBindTexture(GL_TEXTURE_2D, Env2[2]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glEnd();

	//Quad 4
	glBindTexture(GL_TEXTURE_2D, Env2[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glEnd();

	//Quad 5
	glBindTexture(GL_TEXTURE_2D, Env2[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();

	//Quad 6
	glBindTexture(GL_TEXTURE_2D, Env2[5]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, -size + 10, size);   //V1
	glEnd();

}
void draw_Environment3(float size) {
	glColor3f(1.0, 1.0, 1.0); 
	glDisable(GL_LIGHTING);

	//Quad 1
	glBindTexture(GL_TEXTURE_2D, Env3[0]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();
	//Quad 2

	glBindTexture(GL_TEXTURE_2D, Env3[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glEnd();

	//Quad 3
	glBindTexture(GL_TEXTURE_2D, Env3[2]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glEnd();

	//Quad 4
	glBindTexture(GL_TEXTURE_2D, Env3[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glEnd();

	//Quad 5
	glBindTexture(GL_TEXTURE_2D, Env3[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();

	//Quad 6
	glBindTexture(GL_TEXTURE_2D, Env3[5]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, -size + 10, size);   //V1
	glEnd();

}
void draw_Environment4(float size) {
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);

	//Quad 1
	glBindTexture(GL_TEXTURE_2D, Env4[0]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();
	//Quad 2

	glBindTexture(GL_TEXTURE_2D, Env4[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glEnd();

	//Quad 3
	glBindTexture(GL_TEXTURE_2D, Env4[2]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glEnd();

	//Quad 4
	glBindTexture(GL_TEXTURE_2D, Env4[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, size);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glEnd();

	//Quad 5
	glBindTexture(GL_TEXTURE_2D, Env4[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();

	//Quad 6
	glBindTexture(GL_TEXTURE_2D, Env4[5]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size + 10, size);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size + 10, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size + 10, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, -size + 10, size);   //V1
	glEnd();

}





// 물체 박스 
void cubeTextureMapping2() {
	glGenTextures(6, texName2);
	int imgWidth, imgHeight, channels;

	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, texName2[i]);
		char buf[100];
		sprintf(buf, "img/img/b%d.bmp", i);

		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB,
			GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/*glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE)*/;
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

		//X = r * sin(theta) * cos(phi);
		//Y = r * sin(theta) * sin(phi);
		//Z = r * cos(theta);
		//glLoadIdentity();
	}
}
void draw_texture_Cube2(float size) {
	glColor3f(1.0, 1.0, 1.0); // white로 color를 set 해주어야 texture 색상이 제대로 적용됨
	////glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //GL_MODULATE를 하면 원래 텍스쳐랑
	//// 폴리건의 원래 색깔이랑 곱혀져서 덮음, 텍스쳐가 입혀진 표면에 광원 효과 설정도 가능해진다.
	////glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glDisable(GL_LIGHTING);

	//Quad 1
	glBindTexture(GL_TEXTURE_2D, texName2[0]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, size);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();
	//Quad 2

	glBindTexture(GL_TEXTURE_2D, texName2[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glEnd();

	//Quad 3
	glBindTexture(GL_TEXTURE_2D, texName2[2]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, size);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glEnd();

	//Quad 4
	glBindTexture(GL_TEXTURE_2D, texName2[3]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);   //V2
	glEnd();

	//Quad 5
	glBindTexture(GL_TEXTURE_2D, texName2[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, size);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);   //V4
	glEnd();

	//Quad 6
	glBindTexture(GL_TEXTURE_2D, texName2[5]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size , size);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size , -size);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, -size, size);   //V1
	glEnd();

}

void draw_cube_textures()
{
	int size = 4;
	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	//Quad 1
	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 2
	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
  //Quad 3
	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
  //Quad 4
	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
  //Quad 5
	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
  //Quad 6
	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
	glEnd();
}
void draw_textureCube() {
	glColor3f(1.0, 1.0, 1.0);	// white로 color를 set해주어야 texture색상이 제대로 적용 됨!
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			// polygon의 원래 색상은 무시하고 texture로 덮음
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// polygon의 원래 색상과 texture 색상을 곱하여 덮음, texture가 입혀진 표면에 광원 효과 설정 가능
//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		// texture의 색상으로 덮어 씌운다

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0, 0);	// -x axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0);	//x axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(0, -1.0, 0);	// -y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(0, 1.0, 0);	// y axis
	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1.0);	//z axis
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture4);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);	//-z축
	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, -1.0);
	glEnd();
}

void setTextureMapping() {
	int texNum = 1;
	
	int imgWidth1, imgHeight1, channels1;
	uchar* img1 = readImageData("img/silver3.bmp", &imgWidth1, &imgHeight1, &channels1);

	glGenTextures(texNum, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth1, imgHeight1, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//=============================================================================
	int imgWidth2, imgHeight2, channels2;
	uchar* img2 = readImageData("img/blackgray.bmp", &imgWidth2, &imgHeight2, &channels2);


	glGenTextures(texNum, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth2, imgHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//=============================================================================
	int imgWidth3, imgHeight3, channels3;
	uchar* img3 = readImageData("img/black.bmp", &imgWidth3, &imgHeight3, &channels3);

	glGenTextures(texNum, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth3, imgHeight3, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
	
	//=============================================================================
	int imgWidth4, imgHeight4, channels4;
	uchar* img = readImageData("img/red.bmp", &imgWidth4, &imgHeight4, &channels4);

	
	glGenTextures(texNum, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth4, imgHeight4, 0, GL_RGB, GL_UNSIGNED_BYTE, img);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);

	int imgWidth5, imgHeight5, channels5;
	uchar* img4 = readImageData("img/blue.bmp", &imgWidth4, &imgHeight4, &channels4);


	glGenTextures(texNum, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth4, imgHeight4, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
/* Display callback function */

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button==GLUT_LEFT_BUTTON)color_selection = !color_selection;

	glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y) {
	if (dir > 0) {
		if (r > 5) {
			r -= radius;
			X = r * sin(theta) * cos(phi);
			Y = r * sin(theta) * sin(phi);
			Z = r * cos(theta);
			printf("Zoom in!, radius : %f\n", r);
		}
	}
	else {
		if (r < 100) {
			r += radius;
			X = r * sin(theta) * cos(phi);
			Y = r * sin(theta) * sin(phi);
			Z = r * cos(theta);
			printf("Zoom out!, radius : %f\n", r);
		}
	}
	glutPostRedisplay();
}

void passiveMotion(int x, int y)
{
	//printf("Mouse movement x, y = (%d, %d)\n", x, y);
	glutPostRedisplay();
}

void motion(int x, int y)
{
	//printf("Mouse movement x, y = (%d, %d)\n", x, y);
	glutPostRedisplay();
}

void main_menu(int option)
{
	if (option == 99) exit(0);
	else if (option == 1) {
		 theta = 80 * radian, phi = 45 * radian;
		 r = 50;
		 X = r * sin(theta) * cos(phi);
		 Y = r * sin(theta) * sin(phi);
		 Z = r * cos(theta);
	}
	else if (option == 2) {
		 right_left = 0; take_off = 0; front_back = 0; 
		 speed_up = false;
		 speed_down = false;
		 front, back, lt, rt, rst = false;
		 sight_camera, sep_sw = false;
		 seperate = false;
		 temp1 = 15; temp2 = 0; temp3 = 0;
	}
	glutPostRedisplay();
}

void sub_menu(int option)
{
	printf("Submenu %d has been selected\n", option);
	if (option == 1) {
		modelselect = 1;
		environ_map = true;
	}
	else if (option == 2) {
		modelselect = 2;
		environ_map = true;
	}
	else if (option == 3) {
		modelselect = 3;	
		environ_map = true;
	}
	else if (option == 4) {
		modelselect = 4;
		environ_map = true;
	}
	else if (option == 5) {
		modelselect = 5;
		environ_map = false;
	}
	glutPostRedisplay();
}

void add_menu()
{
	int submenu1 = glutCreateMenu(sub_menu);
	glutAddMenuEntry("Morning University", 1);
	glutAddMenuEntry("Night University", 2);
	glutAddMenuEntry("Inha university", 3);
	glutAddMenuEntry("Sky Box", 4);
	glutAddMenuEntry("Remove", 5);

	int mainmenu1 = glutCreateMenu(&main_menu);
	glutAddMenuEntry("Sight reset", 1);
	glutAddMenuEntry("Action reset", 2);
	glutAddSubMenu("Environment", submenu1);
	glutAddMenuEntry("Quit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME); // unit : ms

	if (time - timebase > 1000)
	{
		fps = frame * 1000.f / (time - timebase);
		timebase = time;
		frame = 0;
		//printf("fps : %.0f\n", fps);
	}
	if (seperate == true &&seperate_speed < 2.98 && seperate_speed >= 0) {
		seperate_speed += 0.02;
	}
	if (seperate == false  && seperate_speed <= 3 && seperate_speed > 0.02) {
		seperate_speed -= 0.02;
	}
	//printf("%f\n", seperate_speed);
	//printf("seperate: %d\n", seperate);
	glutPostRedisplay();
}

void resize(int width, int height)
{
	printf("resize func called\n");
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 500, 0, 500);
	gluPerspective(60, (double)width / (double)height, 1, 1000);
	current_height = height;
	current_width = width;
	glMatrixMode(GL_MODELVIEW);
}

void draw_skybox(float size) {

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glDisable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_CUBE_MAP); //??? 어떻게 해야할까
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_nCubeTex);

	glBegin(GL_QUADS);
	//px
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -size, -size);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -size, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, size, size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, size, -size);

	//nx
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -size, -size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -size, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, size, size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, size, -size);

	//py
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, size, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, size, size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, size, -size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, size, -size);

	//ny
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -size, size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -size, size);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -size, -size);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -size, -size);

	//pz
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(size, -size, size);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-size, -size, size);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-size, size, size);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(size, size, size);

	//nz
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(size, -size, -size);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-size, -size, -size);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-size, size, -size);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(size, size, -size);
	glEnd();

	glEnable(GL_LIGHTING);
}

void draw_string(void* font, const char* str, float x_position, float y_position, float z_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void draw_string_switch() {
	char* str = (char*)"Environment => Morning";
	switch (modelselect) {
	case 1:
		str = (char*)"Environment => Morning";
		break;
	case 2:
		str = (char*)"Environment => Night";
		break;
	case 3:
		str = (char*)"Environment => InHa University";
		break;
	case 4:
		str = (char*)"Environment => SkyBox";
		break;
	case 5:
		str = (char*)"Environment => Nothing";
		break;
	default:
		break;
	}
	if (environ_map == false) str = (char*)"Environment => Nothing";
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, str, -10, 9, 5, 1, 1, 0);
}


void draw_string2(void* font, const char* str, float x_position, float y_position, float z_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glutSolidCube(3);
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

int energy;


void draw_string_switch2() {
	if (speed_up == true) {
		for (int i = 0; i < 10000; i++) {
			if (i == 9999)cnt++;
		}
	}
	//printf("%d\n", cnt);
	if (cnt == 1) energy = 1;
	if (cnt == 200) energy = 2;
	if (cnt == 300) energy = 3;
	if (cnt == 400) energy = 4;
	if (cnt == 500) {
		energy = 5;
		cnt =cnt-500;
	}
	char* str = (char*)"Energy *******************";
	switch (energy) {
	case 1:
		str = (char*)"Energy *******************";
		break;
	case 2:
		str = (char*)"Energy **************";
		break;
	case 3:
		str = (char*)"Energy *********";
		break;
	case 4:
		str = (char*)"Energy ****";
		break;
	case 5:
		str = (char*)"Energy *";
		color_selection = true;
		lt = false;
		rt = false;
		back = false;
		front = false;
		speed_down = !speed_down;
		speed_up = false;
		break;
	default:
		str = (char*)"Energy *******************";
		break;
	}
	draw_string2(GLUT_BITMAP_TIMES_ROMAN_24, str, -9, -8, 5, 0, 0, 1);
}

void get_resource1(const char* str)
{
	dron1 = new ObjParser(str);
}

void get_resource2(const char* str)
{
	dron2 = new ObjParser(str);
}
void get_resource3(const char* str)
{
	dron3 = new ObjParser(str);
}

void get_resource4(const char* str)
{
	dron4 = new ObjParser(str);
}

void get_resource5(const char* str)
{
	dron5 = new ObjParser(str);
}
void get_resource6(const char* str)
{
	dron6 = new ObjParser(str);
}
void get_resource7(const char* str)
{
	dron7 = new ObjParser(str);
}
void get_resource8(const char* str)
{
	dron8 = new ObjParser(str);
}
void get_resource9(const char* str)
{
	dron9 = new ObjParser(str);
}
void get_resource10(const char* str)
{
	dron10 = new ObjParser(str);
}

void get_resource11(const char* str)
{
	dron11 = new ObjParser(str);
}

void get_resource12(const char* str)
{
	dron12 = new ObjParser(str);
}

void get_resource13(const char* str)
{
	dron13 = new ObjParser(str);
}

void get_resource14(const char* str)
{
	dron14 = new ObjParser(str);
}

void get_resource15(const char* str)
{
	dron15 = new ObjParser(str);
}
void get_resource16(const char* str)
{
	dron16 = new ObjParser(str);
}
void get_resource17(const char* str)
{
	dron17 = new ObjParser(str);
}
void get_resource18(const char* str)
{
	dron18 = new ObjParser(str);
}
void get_resource19(const char* str)
{
	dron19 = new ObjParser(str);
}
void get_resource20(const char* str)
{
	dron20 = new ObjParser(str);
}
void get_resource21(const char* str)
{
	dron21 = new ObjParser(str);
}
