using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms; 
// для работы с библиотекой OpenGL
using Tao.OpenGl; 
// для работы с библиотекой FreeGLUT
using Tao.FreeGlut; 
// для работы с элементом управления SimpleOpenGLControl
using Tao.Platform.Windows;

namespace Tao_OpenGL_Initialization_Test
{
    internal static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
    

        static void Main()
        {
           
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
