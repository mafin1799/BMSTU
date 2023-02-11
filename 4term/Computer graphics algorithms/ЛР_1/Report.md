# ЗАДАНИЕ К ЛАБОРАТОРНОЙ РАБОТЕ № 1

> [Выполнить шаги, описанные в файле «Тестирование визуализации 3D
сферы»](https://disk.yandex.ru/i/qwnAHflv8tCk_A).

### В результате вы освоите:
- создание простейшего приложения, написанного с использованием
OpenGL в C# (в среде Visual Studio).
- подключение библиотеки Tao.

## Листинг кода
```
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tao.FreeGlut;
using Tao.OpenGl;

namespace Tao_OpenGL_Initialization_Test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            AnT.InitializeContexts();
          
        }

        private void AnT_Load(object sender, EventArgs e)
        {

            // инициализация Glut
            Glut.glutInit(); 
            Glut.glutInitDisplayMode(Glut.GLUT_RGB | Glut.GLUT_DOUBLE | Glut.GLUT_DEPTH);

            //Очистка окна
            Gl.glClearColor(255, 255, 255, 1);

            //Установка порта вывода в соответствии с размерами anT
            Gl.glViewport(0, 0, AnT.Width, AnT.Height);

            //Настройка проекции

            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Glu.gluPerspective(45, (float)AnT.Width / (float)AnT.Height, 0.1, 200);
            Gl.glMatrixMode(Gl.GL_MODELVIEW); 
            Gl.glLoadIdentity();

            //Настройка параметров OpenGL для визуализации
            Gl.glEnable(Gl.GL_DEPTH_TEST);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT); 
            Gl.glLoadIdentity(); Gl.glColor3f(1.0f, 0, 0); 
            Gl.glPushMatrix(); Gl.glTranslated(0, 0, -6); 
            Gl.glRotated(45, 1, 1, 0);
            // рисуем сферу с помощью библиотеки FreeGLUT
            Glut.glutWireSphere(2, 32, 32); 
            Gl.glPopMatrix(); Gl.glFlush(); 
            AnT.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
            
        }
    }
}

```


<div class="page"/>

## Скриншоты

> Перед нажатием

![alt text](https://github.com/mafin1799/BMSTU/blob/main/4term/Computer%20graphics%20algorithms/ЛР_1/1.png?raw=true)
> После нажатия

![alt text](https://github.com/mafin1799/BMSTU/blob/main/4term/Computer%20graphics%20algorithms/ЛР_1/2.png?raw=true)
<div class="page"/>

## Примечание

> При загрузке VS, необходимо загрузить компоненты для создания классических приложений .NET

> При создании проекта необходимо выбрать WindowsForms(.Net), не Майкрософт

> Для вставки кода двойной клик по элементу

> Если все сделали и не компилируется, см. низ инструкции про обработку ошибок