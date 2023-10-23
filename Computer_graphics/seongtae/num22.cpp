//#include "num22.h"
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
//    glutInit(&argc, argv); // glut 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
//    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
//    glutInitWindowSize(WinWidth, WinHeight); // 윈도우의 크기 지정
//    glutCreateWindow("Example22"); // 윈도우 생성(윈도우 이름)
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
//    glutDisplayFunc(drawScene); // 출력 함수의 지정
//    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//    glutKeyboardFunc(KeyBoard);
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
//    unsigned int modelLocation{ NULL };
//    unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
//    unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
//    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetLookAt()));
//    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam.GetPerspective()));
//
//    for (int i = 0; i < 6; ++i) {
//        glBindVertexArray(StageBuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Stage[i].GetMatrix()));
//        glDrawArrays(GL_TRIANGLES, 0, Stage[i].vertex.size());
//    }
//    for (int i = 0; i < 2; ++i) {
//        glBindVertexArray(RobotABuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RobotArm[i].GetMatrix()));
//        glDrawArrays(GL_TRIANGLES, 0, RobotArm[i].vertex.size());
//
//        glBindVertexArray(RobotLBuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RobotLeg[i].GetMatrix()));
//        glDrawArrays(GL_TRIANGLES, 0, RobotLeg[i].vertex.size());
//    }
//
//    for (int i = 0; i < 3; ++i) {
//        glBindVertexArray(RobotBuf[i].vao);
//        modelLocation = glGetUniformLocation(s_program, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Robot[i].GetMatrix()));
//        glDrawArrays(GL_TRIANGLES, 0, Robot[i].vertex.size());
//    }    
//    glBindVertexArray(ObstacleBuf.vao);
//    modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Obstacle[0].GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Obstacle[0].vertex.size());
//    glutSwapBuffers(); // 화면에 출력하기
//}
//
//void KeyBoard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'w':
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].rotate.y = 180;
//        }
//        RobotDir = Down;
//        break;
//    case 's':
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].rotate.y = 0;
//        }
//        RobotDir = Up;
//        break;
//    case 'a':
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].rotate.y = 90;
//            if (i == 2) {
//                Robot[i].rotate.y = 270;
//            }
//        }
//        RobotDir = Left;
//        break;
//    case 'd':
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].rotate.y = 270;
//            if (i == 2) {
//                Robot[i].rotate.y = 90;
//            }
//        }
//        RobotDir = Right;
//        break;
//    case 'o':
//        StageTimer = true;
//        if (StageDir == 0) {
//            StageDir = 1;
//        }
//        else {
//            StageDir = -StageDir;
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
//    case 'j':
//    case 'J':
//        if (!Jump) {
//            Jump = true;
//            JumpDir = 1;
//        }
//        break;
//    case 'i':
//    case 'I':
//        delete[] Robot;
//        delete[] RobotArm;
//        delete[] RobotLeg;
//        for (int i = 0; i < 6; ++i) {
//            Stage[i].vertex.clear();
//            Stage[i].color.clear();
//        }
//        Stage[3].Init();
//        RobotDir = 0;
//        JumpDir = 0;
//        StageDir = 0;
//        StageTimer = false;
//        Init();
//        break;
//    case 'q':
//    case 'Q':
//        delete[] Robot;
//        delete[] RobotArm;
//        delete[] RobotLeg;
//        exit(0);
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void TimerFunc(int value) {
//   
//    if (StageTimer) {
//        Stage[3].axis_translate.z = 0.5;
//        Stage[3].axis_translate.y = -0.5;
//        Stage[3].rotate.x += 5.0 * StageDir;
//        if (Stage[3].rotate.x >= 90) {
//            Stage[3].rotate.x = 90;
//            StageTimer = false;
//        }
//        else if (Stage[3].rotate.x <= 0) {
//            Stage[3].rotate.x = 0;
//            StageTimer = false;
//        }
//    }
//    switch (RobotDir) {
//    case Left:
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].translate.x -= 0.01;
//        }
//        if (LegDir) {
//            RobotLeg[0].rotate.x += 6.0f;
//            RobotArm[0].rotate.y += 4.0f;
//            if (RobotLeg[0].rotate.x >= 40.0f) {
//                LegDir = false;
//            }
//        }
//        else {
//            RobotLeg[0].rotate.x -= 6.0f;
//            RobotArm[0].rotate.y -= 4.0f;
//            if (RobotLeg[0].rotate.x <= -40.0f) {
//                LegDir = true;
//            }
//        }
//        RobotLeg[1].rotate = -RobotLeg[0].rotate;
//        RobotArm[1].rotate.y = -RobotArm[0].rotate.y;
//        if (On_Obst && !Collide() && !Jump) {
//            On_Obst = false;
//            Jump = true;
//            JumpDir = -1;
//        }
//        Can_Move();
//        break;
//    case Right:
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].translate.x += 0.01;
//        }
//        if (LegDir) {
//            RobotLeg[0].rotate.x += 6.0f;
//            RobotArm[0].rotate.y += 4.0f;
//            if (RobotLeg[0].rotate.x >= 40.0f) {
//                LegDir = false;
//            }
//        }
//        else {
//            RobotLeg[0].rotate.x -= 6.0f;
//            RobotArm[0].rotate.y -= 4.0f;
//            if (RobotLeg[0].rotate.x <= -40.0f) {
//                LegDir = true;
//            }
//        }
//        RobotLeg[1].rotate = -RobotLeg[0].rotate;
//        RobotArm[1].rotate.y = -RobotArm[0].rotate.y;
//        if (On_Obst && !Collide() && !Jump) {
//            On_Obst = false;
//            Jump = true;
//            JumpDir = -1;
//        }
//        Can_Move();
//        break;
//    case Up:
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].translate.z += 0.01;
//        }
//        if (LegDir) {
//            RobotLeg[0].rotate.x += 6.0f;
//            RobotArm[0].rotate.y += 4.0f;
//            if (RobotLeg[0].rotate.x >= 40.0f) {
//                LegDir = false;
//            }
//        }
//        else {
//            RobotLeg[0].rotate.x -= 6.0f;
//            RobotArm[0].rotate.y -= 4.0f;
//            if (RobotLeg[0].rotate.x <= -40.0f) {
//                LegDir = true;
//            }
//        }
//        RobotLeg[1].rotate = -RobotLeg[0].rotate;
//        RobotArm[1].rotate.y = -RobotArm[0].rotate.y;
//        if (On_Obst && !Collide() && !Jump) {
//            On_Obst = false;
//            Jump = true;
//            JumpDir = -1;
//        }
//        Can_Move();
//        break;
//    case Down:
//        for (int i = 0; i < 3; ++i) {
//            Robot[i].translate.z -= 0.01;
//        }
//        if (LegDir) {
//            RobotLeg[0].rotate.x += 6.0f;
//            RobotArm[0].rotate.y += 4.0f;
//            if (RobotLeg[0].rotate.x >= 40.0f) {
//                LegDir = false;
//            }
//        }
//        else {
//            RobotLeg[0].rotate.x -= 6.0f;
//            RobotArm[0].rotate.y -= 4.0f;
//            if (RobotLeg[0].rotate.x <= -40.0f) {
//                LegDir = true;
//            }
//        }
//        RobotLeg[1].rotate = -RobotLeg[0].rotate;
//        RobotArm[1].rotate.y = -RobotArm[0].rotate.y;
//        if (On_Obst && !Collide() && !Jump) {
//            On_Obst = false;
//            Jump = true;
//            JumpDir = -1;
//        }
//        Can_Move();
//        break;
//    default:
//        break;
//    }
//
//    if (Jump) {
//        if (JumpDir == 1) {
//            for (int i = 0; i < 3; ++i) {
//                Robot[i].translate.y += 0.01 * JumpDir;
//            }
//            if (Robot[0].translate.y >= 0.3) {
//                JumpDir = -1;
//            }
//        }
//        else {
//            for (int i = 0; i < 3; ++i) {
//                Robot[i].translate.y += 0.01 * JumpDir;
//            }
//            if (Robot[0].translate.y <= 0.2) {
//                JumpDir = 0;
//                Jump = false;
//                float dis = 0.2 - Robot[0].translate.y;
//                for (int i = 0; i < 3; ++i) {
//                    Robot[i].translate.y += dis;
//                }
//            }
//            else if (Collide()) {
//                On_Obst = true;
//                JumpDir = 0;
//                Jump = false;
//                float dis = Obstacle[0].GetBackPos().y - RobotLeg[0].GetFrontPos().y;
//                for (int i = 0; i < 3; ++i) {
//                    Robot[i].translate.y += dis;
//                }
//            }
//        }
//    }
//    glutTimerFunc(100, TimerFunc, 1);
//
//    glutPostRedisplay();
//}