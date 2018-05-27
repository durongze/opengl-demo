 
 #include <cstdio>
 #include <cstdlib>
 #include <GL/glut.h>
 #include <cmath>
 #include <ctime>
 
 //////////////////////////////////////////////////  
 //global  
 float g_fWidth = 500;
 float g_fHeight = 500;
 float g_fDepth = 100;
 float g_fAngle = .0;
 
 struct Button{
     float m_fPosX;      //表示在正交投影坐标系(左下角为坐标原点)的坐标，  
     float m_fPosY;
     float m_fWidth;     //屏幕像素单位  
     float m_fHeight;
 
     bool m_bPressed;
     void Render()
     {
         glPushMatrix();
         {
             //将中心位于原点的cube移动到使cube左下角坐标为m_fPosX,m_fPosY的位置  
             //必须考虑cube的自身长宽  
             glTranslatef(m_fPosX+m_fWidth/2, m_fPosY+m_fHeight/2, -2.0);        //-2.0只是为了按钮可见  
             if( m_bPressed )
             {
                 //double scaleAmt = 10.0 * sin( (double)rand() );  
                 //double scaleAmt = sin( (double)rand() );  
                 glScalef(0.9, 0.9, 1.0);
             }
             //cube中心位于原点  
             glScalef (m_fWidth, m_fHeight, 5.0);
             glutSolidCube(1.0);
         }
     }
     bool OnMouseDown(int mousex, int mousey)
     {
         //鼠标的位置：mousex，mousey坐标系是原点位于左上角  
         //必须将mousey变换到原点位于左下角的坐标系中  
         mousey = g_fHeight-mousey;
         if( mousex > m_fPosX && mousex < m_fPosX+m_fWidth &&
                 mousey > m_fPosY && mousey < m_fPosY+m_fHeight )
         {
             printf("button is pressed .... /n");
             m_bPressed = true;
 
             return true;
         }
         return false;
     }
     void OnMouseUp()
     {
         m_bPressed = false;
     }
 };
 Button* pBtn;
 
 void init(void)
 {
     glClearColor (0.0, 0.0, 0.0, 0.0);
     glShadeModel (GL_SMOOTH);
 
     pBtn = new Button;
     pBtn->m_bPressed = false;
     pBtn->m_fPosX = 40;
     pBtn->m_fPosY = 480;
     pBtn->m_fWidth = 60;
     pBtn->m_fHeight = 20;
     printf("**********button pos: 40/t480/n");
 }
 
 void display(void)
 {
     glClear (GL_COLOR_BUFFER_BIT);
     glColor3f (1.0, 1.0, 1.0);
 
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(0, g_fWidth, 0, g_fHeight, 0, g_fDepth);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     pBtn->Render();
 
     // 绘制cube物体，  
     glMatrixMode (GL_PROJECTION);       //回复原有的设置  
     glLoadIdentity ();
     gluPerspective(60,1.0,1.5,20);
     glMatrixMode (GL_MODELVIEW);
     glLoadIdentity ();
     /* viewing transformation  */
     gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
     glRotatef(g_fAngle, 0.0, 1.0, 0.0);
     glScalef (1.0, 2.0, 1.0);      /* modeling transformation */
     glutWireCube (1.0);
     //glFlush();  
     glutSwapBuffers();
 }
 
 void reshape (int w, int h)
 {
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity ();
     gluPerspective(60,1.0,1.5,20);
     glMatrixMode (GL_MODELVIEW);
 }
 
 void keyboard(unsigned char key, int x, int y)
 {
     switch (key) {
         case 27:
             exit(0);
             break;
     }
 }
 
 void mouse(int button, int state, int x, int y)
 {
     if(button==GLUT_LEFT_BUTTON)
         switch(state)
         {
             case GLUT_DOWN:
                 //左键按下：  
                 printf("Mouse pos : %d/t%d/n", x, 500-y);
                 if( pBtn->OnMouseDown(x, y) )
                     g_fAngle += 2.0;
                 break;
 
             case GLUT_UP:
                 pBtn->OnMouseUp();
                 break;
         }
     glutPostRedisplay();
 }
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc( mouse );
    glutMainLoop();
    return 0;
}
/*
ldd exec 
        linux-vdso.so.1 =>  (0x00007fff0f3e3000)
        libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f83b4ffc000)
        libglut.so.3 => /lib64/libglut.so.3 (0x00007f83b4db1000)
        libGL.so.1 => /home/duyongze/opt/mesa-18.0.2/lib/libGL.so.1 (0x00007f83b4b45000)
        libGLU.so.1 => /lib64/libGLU.so.1 (0x00007f83b48c5000)
        libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f83b45be000)
        libm.so.6 => /lib64/libm.so.6 (0x00007f83b42bb000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f83b40a5000)
        libc.so.6 => /lib64/libc.so.6 (0x00007f83b3ce4000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f83b5232000)
        libXext.so.6 => /lib64/libXext.so.6 (0x00007f83b3ad1000)
        libX11.so.6 => /lib64/libX11.so.6 (0x00007f83b3793000)
        libXi.so.6 => /lib64/libXi.so.6 (0x00007f83b3583000)
        libXxf86vm.so.1 => /lib64/libXxf86vm.so.1 (0x00007f83b337c000)
        libz.so.1 => /lib64/libz.so.1 (0x00007f83b3166000)
        libexpat.so.1 => /home/duyongze/opt//expat-2.2.5/lib/libexpat.so.1 (0x00007f83b2f2f000)
        libxcb-dri3.so.0 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-dri3.so.0 (0x00007f83b2d2a000)
        libxcb-xfixes.so.0 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-xfixes.so.0 (0x00007f83b2b21000)
        libxcb-present.so.0 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-present.so.0 (0x00007f83b291c000)
        libxcb-sync.so.1 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-sync.so.1 (0x00007f83b2714000)
        libxshmfence.so.1 => /home/duyongze/opt//libxshmfence-1.3/lib/libxshmfence.so.1 (0x00007f83b2511000)
        libglapi.so.0 => /home/duyongze/opt/mesa-18.0.2/lib/libglapi.so.0 (0x00007f83b22df000)
        libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f83b20dc000)
        libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f83b1ed6000)
        libX11-xcb.so.1 => /lib64/libX11-xcb.so.1 (0x00007f83b1cd3000)
        libxcb-glx.so.0 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-glx.so.0 (0x00007f83b1ab3000)
        libxcb-dri2.so.0 => /home/duyongze/opt//libxcb-1.13/lib/libxcb-dri2.so.0 (0x00007f83b18ae000)
        libxcb.so.1 => /home/duyongze/opt//libxcb-1.13/lib/libxcb.so.1 (0x00007f83b167c000)
        libXau.so.6 => /lib64/libXau.so.6 (0x00007f83b1478000)
        libdrm.so.2 => /home/duyongze/opt/libdrm2492/lib/libdrm.so.2 (0x00007f83b1267000)
        libdl.so.2 => /lib64/libdl.so.2 (0x00007f83b1062000)
        */

