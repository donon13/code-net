# code-net
using System;
using System.Drawing;
using System.Windows.Forms;

namespace Sudoku
{
    public partial class Form1 : Form
    {
        private int[,] board = new int[9, 9];
        private TextBox[,] boxes = new TextBox[9, 9];
        private Button solveButton = new Button();

        public Form1()
        {
            InitializeComponent();
            InitializeBoard();
            InitializeSolveButton();
        }

        private void InitializeBoard()
        {
            int boxSize = 50;

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    TextBox box = new TextBox();
                    box.Size = new Size(boxSize, boxSize);
                    box.Location = new Point(boxSize * j, boxSize * i);
                    box.TextAlign = HorizontalAlignment.Center;
                    box.MaxLength = 1;
                    box.KeyPress += Box_KeyPress;
                    boxes[i, j] = box;
                    this.Controls.Add(box);
                }
            }
        }

        private void InitializeSolveButton()
        {
            solveButton.Text = "Solve";
            solveButton.Size = new Size(80, 30);
            solveButton.Location = new Point(350, 225);
            solveButton.Click += SolveButton_Click;
            this.Controls.Add(solveButton);
        }

        private void Box_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void SolveButton_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    int value;
                    bool success = int.TryParse(boxes[i, j].Text, out value);
                    board[i, j] = success ? value : 0;
                }
            }

            if (Solver.Solve(board))
            {
                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        boxes[i, j].Text = board[i, j].ToString();
                    }
                }
            }
            else
            {
                MessageBox.Show("No solution found.");
            }
        }
    }

    public static class Solver
    {
        public static bool Solve(int[,] board)
        {
            int row = 0;
            int col = 0;

            if (!FindUnassignedLocation(board, ref row, ref col))
            {
                return true;
            }

            for (int num = 1; num <= 9; num++)
            {
                if (IsValid(board, row, col, num))
                {
                    board[row, col] = num;

                    if (Solve(board))
                    {
                        return true;
                    }

                    board[row, col] = 0;
                }
            }

            return false;
        }

        private static bool FindUnassignedLocation(int[,] board, ref int row, ref int col)
        {
            for (row = 0; row < 9; row++)
            {
                for (col = 0; col < 9; col++)
                {
                    if (board[row, col] == 0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        private static bool IsValid(int[,] board, int row, int col, int num)
        {
            for
