//#include "num21.h"
//
//
//GLvoid drawScene(GLvoid);
//void KeyBoard(unsigned char key, int x, int y);
//void TimerFunc(int value);
//
//void main(int argc, char** argv)
//{
//    Menu();
//    Init();
//
//    glutInit(&argc, argv); // glut �ʱ�ȭ
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
//    glutInitWindowPosition(0, 0); // �������� ��ġ ����
//    glutInitWindowSize(WinWidth, WinHeight); // �������� ũ�� ����
//    glutCreateWindow("Example21"); // ������ ����(������ �̸�)
//    //--- GLEW �ʱ�ȭ�ϱ�
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    glutTimerFunc(10, TimerFunc, 1);
//
//    //--- ���̴� �о�ͼ� ���̴� ���α׷� �����
//    InitShader();
//    InitBuffer();
//
//    glutDisplayFunc(drawScene); // ��� �Լ��� ����
//    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
//    glutKeyboardFunc(KeyBoard);
//    glutMainLoop(); // �̺�Ʈ ó�� ���� 
//}
//
//GLvoid drawScene()
//{
//    glDepthFunc(GL_LESS);
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glUseProgram(s_program);
//
//    unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
//    unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
//    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetLookAt()));
//    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam.GetPerspective()));
//
//    glBindVertexArray(CBuf[15].vao);
//
//    unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Base.GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Base.vertex.size());
//    
//    for (int i = 0; i < 15; ++i) {
//        glBindVertexArray(CBuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Cubes[i].GetMatrix()));
//        if (Cubes[i].show) {
//            glDrawArrays(GL_TRIANGLES, 0, Cubes[i].vertex.size());
//        }
//    }
//
//    for (int i = 0; i < 2; ++i) {
//        glBindVertexArray(EBuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Erase[i].GetMatrix()));
//        glDrawArrays(GL_TRIANGLES, 0, Erase[i].vertex.size());
//    }
//
//    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
//}
//
//void KeyBoard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'w':
//        for (int i = 0; i < 2; ++i) {
//            Erase[i].translate.z -= 0.05;
//        }
//        Collide();
//        break;
//    case 's':
//        for (int i = 0; i < 2; ++i) {
//            Erase[i].translate.z += 0.05;
//        }
//        Collide();
//        break;
//    case 'a':
//        for (int i = 0; i < 2; ++i) {
//            Erase[i].translate.x -= 0.05;
//        }
//        Collide();
//        break;
//    case 'd':
//        for (int i = 0; i < 2; ++i) {
//            Erase[i].translate.x += 0.05;
//        }
//        Collide();
//        break;
//    case 'r':
//    {
//        cam.pre_rotate.y = 5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'R':
//    {
//        cam.pre_rotate.y = -5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'c':
//    case 'C':
//        delete[] Cubes;
//        delete[] Erase;
//        Init();
//
//        break;
//    case 'q':
//    case 'Q':
//        delete[] Cubes;
//        delete[] Erase;
//        exit(0);
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void TimerFunc(int value) {
//   int result = Collide();
//
//   if (Cubes[result].pre_scale.y > 0.0) {
//       Cubes[result].pre_scale.y -= 0.01;
//       Cubes[result].pre_scale.x -= 0.01;
//       Cubes[result].pre_scale.z -= 0.01;
//   }
//   else {
//       Cubes[result].show = false;
//   }
//   glutTimerFunc(10, TimerFunc, 1);
//
//   glutPostRedisplay();
//}