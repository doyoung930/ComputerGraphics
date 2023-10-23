//#include "num23.h"
//#include "Framework.h"
//
//GLvoid drawScene(GLvoid);
//void KeyBoard(unsigned char key, int x, int y);
//void Mouse(int button, int state, int x, int y);
//void Motion(int x, int y);
//void TimerFunc(int value);
//CFramework* framework;
//
//void main(int argc, char** argv)
//{
//    Menu();
//    Init();
//
//    glutInit(&argc, argv); // glut 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
//    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
//    glutInitWindowSize(WinWidth, WinHeight); // 윈도우의 크기 지정
//    glutCreateWindow("Example23"); // 윈도우 생성(윈도우 이름)
//    //--- GLEW 초기화하기
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    glutTimerFunc(100, TimerFunc, 1);
//
//    //--- 세이더 읽어와서 세이더 프로그램 만들기
//    InitShader();
//    InitBuffer();
//
//    framework = new CFramework();
//
//    glutDisplayFunc(drawScene); // 출력 함수의 지정
//    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//    glutKeyboardFunc(KeyBoard);
//    glutMouseFunc(Mouse);
//    glutMotionFunc(Motion);
//    glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene()
//{
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glUseProgram(s_program);
//
//    glm::mat4 color = { 1.0, 0.0, 0.0, 0.0,
//                       0.0, 1.0, 0.0, 0.0,
//                       0.0, 0.0, 1.0, 0.0,
//                       0.0, 0.0, 0.0, 1.0 };
//
//    unsigned int modelLocation{ NULL };
//    unsigned int colorLocation = glGetUniformLocation(s_program, "GluColor");
//    unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
//    unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
//    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetLookAt()));
//    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam.GetPerspective()));
//    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
//    
//    framework->Render();
//
//    glutSwapBuffers(); // 화면에 출력하기
//}
//
//void KeyBoard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'b':
//    case 'B':
//        for (int i = 0; i < 5; ++i) {
//            if (!ball[i].show) {
//                ball[i].show = true;
//                ball[i].translate = { uidt(engine), uidt(engine), uidt(engine) };
//                ball[i].dir = uiddir(engine);
//                break;
//            }
//        }
//        break;
//    case 'y':
//    {
//        cam.pre_rotate.y = 5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'Y':
//    {
//        cam.pre_rotate.y = -5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'z':
//        cam.translate.z += 0.1f;
//        break;
//    case 'Z':
//        cam.translate.z -= 0.1f;
//        break;
//    case 'x':
//        cam.translate.x += 0.1f;
//        break;
//    case 'X':
//        cam.translate.x -= 0.1f;
//        break;
//    case 'q':
//    case 'Q':
//        //delete[] Cubes;
//        delete framework;
//        exit(0);
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void Mouse(int button, int state, int x, int y) {
//    if ((button == GLUT_LEFT_BUTTON) && state == GLUT_DOWN) {
//        Drag = true;
//        mousex = x;
//    }
//    else {
//        Drag = false;
//    }
//}
//
//void Motion(int x, int y) {
//    if (Drag) {
//        if (mousex - x > 0) {
//            cam.rotate.z -= (mousex - x) * 0.5f;
//            //Stage[0].rotate.z -= (mousex - x) * 0.5f;
//        }
//        else if (mousex - x < 0) {
//            cam.rotate.z -= (mousex - x) * 0.5f;
//            // Stage[0].rotate.z -= (mousex - x) * 0.5f;
//        }
//        else {}
//        mousex = x;
//    }
//}
//
//void TimerFunc(int value) {
//    for (int i = 0; i < 5; ++i) {
//        if (ball[i].show) {
//            switch (ball[i].dir) {
//            case 1: //z축++
//                ball[i].translate.z += 0.05;
//                if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 2;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 2: //z축--
//                ball[i].translate.z -= 0.05;
//                if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 1;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 3: //x축++
//                ball[i].translate.x += 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 4;
//                    ball[i].translate.x = 0.45;
//                }
//                break;
//            case 4: //x축--
//                ball[i].translate.x -= 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 3;
//                    ball[i].translate.x = -0.45;
//                }
//                break;
//            case 5: //y축++
//                ball[i].translate.y += 0.05;
//                if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 6;
//                    ball[i].translate.y = 0.45;
//                }
//                break;
//            case 6: //y축--
//                ball[i].translate.y -= 0.05;
//                if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 5;
//                    ball[i].translate.y = -0.45;
//                }
//                break;
//            case 7: //x축++ y축++
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y += 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 8;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 8;
//                    ball[i].translate.y = 0.45;
//                }
//                break;
//            case 8: //x축-- y축--
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y -= 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 7;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 7;
//                    ball[i].translate.y = -0.45;
//                }
//                break;
//            case 9: //x축++ y축--
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y -= 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 10;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 10;
//                    ball[i].translate.y = -0.45;
//                }
//                break;
//            case 10: //x축-- y축++
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y += 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 9;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 9;
//                    ball[i].translate.y = 0.45;
//                }
//                break;
//            case 11: //x축++ z축++
//                ball[i].translate.x += 0.05;
//                ball[i].translate.z += 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 12;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 12;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 12: //x축-- z축--
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.z -= 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 11;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 11;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 13: //x축++ z축--
//                ball[i].translate.x += 0.05;
//                ball[i].translate.z -= 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 14;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 14;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 14: //x축-- z축++
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.z += 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 13;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 13;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 15: //y축++ z축++
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z += 0.05;
//                if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 16;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 16;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 16: //y축-- z축--
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z -= 0.05;
//                if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 15;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 15;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 17: //y축++ z축--
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z -= 0.05;
//                if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 18;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 18;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 18: //y축-- z축++
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z += 0.05;
//                if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 17;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 17;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 19: //x축++ y축++ z축++
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z += 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 20;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 20;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 20;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 20: //x축-- y축-- z축--
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z -= 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 19;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 19;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 19;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 21: //x축++ y축++ z축--
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z -= 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 22;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 22;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= 0.5) {
//                    ball[i].dir = 22;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 22: //x축-- y축-- z축++
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z += 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 21;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 21;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 21;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 23: //x축++ y축-- z축++
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z += 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 24;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 24;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 24;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 24: //x축-- y축++ z축--
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z -= 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 23;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 23;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 23;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            case 25: //x축-- y축++ z축++
//                ball[i].translate.x -= 0.05;
//                ball[i].translate.y += 0.05;
//                ball[i].translate.z += 0.05;
//                if (-0.05 + ball[i].translate.x <= -0.5) {
//                    ball[i].dir = 26;
//                    ball[i].translate.x = -0.45;
//                }
//                else if (0.05 + ball[i].translate.y >= 0.5) {
//                    ball[i].dir = 26;
//                    ball[i].translate.y = 0.45;
//                }
//                else if (0.05 + ball[i].translate.z >= 0.5) {
//                    ball[i].dir = 26;
//                    ball[i].translate.z = 0.45;
//                }
//                break;
//            case 26: //x축++ y축-- z축--
//                ball[i].translate.x += 0.05;
//                ball[i].translate.y -= 0.05;
//                ball[i].translate.z -= 0.05;
//                if (0.05 + ball[i].translate.x >= 0.5) {
//                    ball[i].dir = 25;
//                    ball[i].translate.x = 0.45;
//                }
//                else if (-0.05 + ball[i].translate.y <= -0.5) {
//                    ball[i].dir = 25;
//                    ball[i].translate.y = -0.45;
//                }
//                else if (-0.05 + ball[i].translate.z <= -0.5) {
//                    ball[i].dir = 25;
//                    ball[i].translate.z = -0.45;
//                }
//                break;
//            default:
//                break;
//            }
//        }
//    }
//
//    // BoxMove();
//    // NewMove();
//    glutTimerFunc(100, TimerFunc, 1);
//
//    glutPostRedisplay();
//}