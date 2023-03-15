'''
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Tao.OpenGl;
using Tao.FreeGlut;
using Tao.Platform.Windows;

namespace lab3
{
    






    public partial class Form1 : Form
    {

        //sizeGraph

        int X_min = 0, Y_min = 0, X_max = 0, Y_max = 0;

        // размеры окна 
        double ScreenW, ScreenH;

        // отношения сторон окна визуализации 
        // для корректного перевода координат мыши в координаты, 
        // принятые в программе 

        private float devX;
        private float devY;

        // массив, который будет хранить значения x,y точек графика 
        private float[,] GrapValuesArray;
        // количество элементов в массиве 
        private int elements_count = 0;

        // флаг, означающий, что массив с значениями координат графика пока еще не заполнен 
        private bool not_calculate = true;

        // номер ячейки массива, из которой будут взяты координаты для красной точки 
        // для визуализации текущего кадра 
        private int pointPosition = 0;

        // вспомогательные переменные для построения линий от курсора мыши к координатным осям 
        float lineX, lineY;

        // текущение координаты курсора мыши 
        float Mcoord_X = 0, Mcoord_Y = 0;

        // функция обработчик события таймера 
        private void PointInGrap_Tick(object sender, EventArgs e)
        {

            // если мы дошли до последнего элемента массива 
            if (pointPosition == elements_count - 1)
                pointPosition = 0; // переходим к начальному элементу 

            // функция визуализации 
            Draw();

            // переход к следующему элементу массива 
            pointPosition++;

        }


        // функция, производящая вычисления координат графика 
        // и заносящая их в массив GrapValuesArray 
        private void functionCalculation()
        {

            // определение локальных переменных X и Y 
            float x = 0, y = 0;

            // инициализация массива, который будет хранить значение 300 точек, 
            // из которых будет состоять график 

            GrapValuesArray = new float[300, 2];

            // счетчик элементов массива 
            elements_count = 0;

            // вычисления всех значений y для x, принадлежащего промежутку от -15 до 15 с шагом в 0.01f 
            for (x = X_min; x < X_max; x += 0.1f)
            {
                // вычисление y для текущего x 
                // по формуле y = (float)Math.Sin(x)*3 + 1; 
                // эта строка задает формулу, описывающую график функции для нашего уравнения y = f(x). 
                y = (float)Math.Sin(x) * 3 + 1;

                // запись координаты x 
                GrapValuesArray[elements_count, 0] = x;
                // запись координаты y 
                GrapValuesArray[elements_count, 1] = y;
                // подсчет элементов 
                elements_count++;

            }

            // изменяем флаг, сигнализировавший о том, что координаты графика не вычислены 
            not_calculate = false;

        }

        // визуализация графика 
        private void DrawDiagram()
        {

            // проверка флага, сигнализирующего о том, что координаты графика вычислены 
            if (not_calculate)
            {
                // если нет, то вызываем функцию вычисления координат графика 
                functionCalculation();
            }

            // стартуем отрисовку в режиме визуализации точек 
            // объединяемых в линии (GL_LINE_STRIP) 
            Gl.glBegin(Gl.GL_LINE_STRIP);

            // рисуем начальную точку 
            Gl.glVertex2d(GrapValuesArray[0, 0], GrapValuesArray[0, 1]);

            // проходим по массиву с координатами вычисленных точек 
            for (int ax = 1; ax < elements_count; ax += 2)
            {
                // передаем в OpenGL информацию о вершине, участвующей в построении линий 
                Gl.glVertex2d(GrapValuesArray[ax, 0], GrapValuesArray[ax, 1]);
            }

            // завершаем режим рисования 
            Gl.glEnd();
            // устанавливаем размер точек, равный 5 пикселям 
            Gl.glPointSize(5);
            // устанавливаем текущим цветом - красный цвет 
            Gl.glColor3f(255, 0, 0);
            // активируем режим вывода точек (GL_POINTS) 
            Gl.glBegin(Gl.GL_POINTS);
            // выводим красную точку, используя ту ячейку массива, до которой мы дошли (вычисляется в функции обработчике событий таймера) 
            Gl.glVertex2d(GrapValuesArray[pointPosition, 0], GrapValuesArray[pointPosition, 1]);
            // завершаем режим рисования 
            Gl.glEnd();
            // устанавливаем размер точек равный единице 
            Gl.glPointSize(1);

        }

        // функция, управляющая визуализацией сцены 
        private void Draw()
        {

            // очистка буфера цвета и буфера глубины 
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);

            // очищение текущей матрицы 
            Gl.glLoadIdentity();

            // установка черного цвета 
            Gl.glColor3f(0, 0, 0);

            // помещаем состояние матрицы в стек матриц 
            Gl.glPushMatrix();

            // выполняем перемещение в пространстве по осям X и Y 
            Gl.glTranslated(X_max, Y_max, 0);

            // активируем режим рисования (Указанные далее точки будут выводиться как точки GL_POINTS) 
            Gl.glBegin(Gl.GL_POINTS);

            // с помощью прохода вдумя циклами, создаем сетку из точек 
            for (int ax = X_min; ax < X_max; ax++)
            {
                for (int bx = Y_min; bx < Y_max; bx++)
                {
                    // вывод точки 
                    Gl.glVertex2d(ax, bx);
                }
            }

            // завершение режима рисования примитивов 
            Gl.glEnd();

            // активируем режим рисования, каждые 2 последовательно вызванные команды glVertex 
            // объединяются в линии 
            Gl.glBegin(Gl.GL_LINES);

            // далее мы рисуем координатные оси и стрелки на их концах 
            Gl.glVertex2d(0, Y_min);
            Gl.glVertex2d(0, Y_max);

            Gl.glVertex2d(X_min, 0);
            Gl.glVertex2d(X_max, 0);

            // вертикальная стрелка 
            Gl.glVertex2d(0, Y_max);
            Gl.glVertex2d(0.1, Y_max - 0.5);
            Gl.glVertex2d(0, Y_max);
            Gl.glVertex2d(-0.1, Y_max - 0.5);

            // горизонтальная трелка 
            Gl.glVertex2d(X_max, 0);
            Gl.glVertex2d(X_max - 0.5, 0.1);
            Gl.glVertex2d(X_max, 0);
            Gl.glVertex2d(X_max - 0.5, -0.1);

            // завершаем режим рисования 
            Gl.glEnd();

            // выводим подписи осей "x" и "y" 
            PrintText2D(X_max +0.5f, 0, "x");
            PrintText2D(0.5f,Y_max - 0.5f, "y");

            // вызываем функцию рисования графика 
            DrawDiagram();

            // возвращаем матрицу из стека 
            Gl.glPopMatrix();

            // выводим текст со значением координат возле курсора 
            PrintText2D(devX * Mcoord_X + 0.2f, (float)ScreenH - devY * Mcoord_Y + 0.4f, "[ x: " + (devX * Mcoord_X - 15).ToString() + " ; y: " + ((float)ScreenH - devY * Mcoord_Y - 15).ToString() + "]");

            // устанавливаем красный цвет 
            Gl.glColor3f(255, 0, 0);

            // включаем режим рисования линий, для того чтобы нарисовать 
            // линии от курсора мыши к координатным осям 
            Gl.glBegin(Gl.GL_LINES);

            Gl.glVertex2d(lineX, 15);
            Gl.glVertex2d(lineX, lineY);
            Gl.glVertex2d(15, lineY);
            Gl.glVertex2d(lineX, lineY);

            Gl.glEnd();

            // дожидаемся завершения визуализации кадра 
            Gl.glFlush();

            // сигнал для обновление элемента реализующего визуализацию. 
            AnT.Invalidate();

        }



        // функция визуализации текста 
        private void PrintText2D(float x, float y, string text)
        {

            // устанавливаем позицию вывода растровых символов 
            // в переданных координатах x и y. 
            Gl.glRasterPos2f(x, y);

            // в цикле foreach перебираем значения из массива text, 
            // который содержит значение строки для визуализации 
            foreach (char char_for_draw in text)
            {
                // символ C визуализируем с помощью функции glutBitmapCharacter, используя шрифт GLUT_BITMAP_9_BY_15. 
                Glut.glutBitmapCharacter(Glut.GLUT_BITMAP_9_BY_15, char_for_draw);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text) || string.IsNullOrEmpty(textBox2.Text) || string.IsNullOrEmpty(textBox3.Text) || string.IsNullOrEmpty(textBox4.Text))
            {
                label1.Text = "Введите значения";
                return;
            }
            X_min = int.Parse(textBox1.Text);
            X_max = int.Parse(textBox2.Text);
            Y_min = int.Parse(textBox3.Text);
            Y_max = int.Parse(textBox4.Text);

            update();

            Console.WriteLine("Пока мир...");
            Console.WriteLine(X_min);
            Console.WriteLine(X_max);
            Console.WriteLine(Y_min);
            Console.WriteLine(Y_max);
        }


        // обработка движения мыши над элементом AnT 
        private void AnT_MouseMove(object sender, MouseEventArgs e)
        {

            // сохраняем координаты мыши 
            Mcoord_X = e.X;
            Mcoord_Y = e.Y;

            // вычисляем параметры для будущей дорисовки линий от указателя мыши к координатным осям. 
            lineX = devX * e.X;
            lineY = (float)(ScreenH - devY * e.Y);

        }


        public Form1()
        {
            InitializeComponent();
            AnT.InitializeContexts();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            // инициализация библиотеки glut 
            Glut.glutInit();
            // инициализация режима экрана 

            X_min = int.Parse(textBox1.Text);
            X_max = int.Parse(textBox2.Text);
            Y_min = int.Parse(textBox3.Text);
            Y_max = int.Parse(textBox4.Text);


            update();


           


        }

        public void update()
        {
            Glut.glutInitDisplayMode(Glut.GLUT_RGB | Glut.GLUT_DOUBLE);

            // установка цвета очистки экрана (RGBA) 
            Gl.glClearColor(255, 255, 255, 1);

            // установка порта вывода 
            Gl.glViewport(0, 0, AnT.Width, AnT.Height);

            // активация проекционной матрицы 
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            // очистка матрицы 
            Gl.glLoadIdentity();

            // если нет, то вызываем функцию вычисления координат графика 
            functionCalculation();

            // определение параметров настройки проекции в зависимости от размеров сторон элемента AnT. 

            ScreenW = X_max - X_min;
                ScreenH = Y_max - Y_min;

                Glu.gluOrtho2D(0.0, ScreenW, 0.0, ScreenH);
           

            // сохранение коэффициентов, которые нам необходимы для перевода координат указателя в оконной системе в координаты, 
            // принятые в нашей OpenGL сцене 
            devX = (float)ScreenW / (float)AnT.Width;
            devY = (float)ScreenH / (float)AnT.Height;

            // установка объектно-видовой матрицы 
            Gl.glMatrixMode(Gl.GL_MODELVIEW);

            // старт счетчика, отвечающего за вызов функции визуализации сцены 
            PointInGrap.Start();
        }

    }
}

'''
