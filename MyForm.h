#pragma once
#include <time.h>
#include <cstdlib>

namespace LifeSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Drawing::Imaging;


	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		Graphics^ graphics;
		int resolution;
		int cols;
		int rows;
		bool** field;
		bool** newfield;
		int СountingGeneration = 0;
		bool RenderActivity = false;
	private: System::Windows::Forms::Button^ NextIteration;


	public:

		MyForm(void)
		{
			InitializeComponent();
			CreateGraphics();
		}

	private:

		bool ValidateMousePosition(int x, int y)
		{
			return x >= 0 && y >= 0 && x < cols&& y < rows;
		}
		int СountingNeighbors(int x, int y)
		{
			int count = 0;
			for (int dx = -1;dx <= 1;dx++)
			{
				for (int dy = -1;dy <= 1;dy++)
				{
					int col = (x + dx + cols) % cols;
					int row = (y + dy + rows) % rows;
					bool IsSelfChecking = col == x && row == y;
					bool ExistenceOfLife = field[col][row];
					if (ExistenceOfLife == 1 && IsSelfChecking == 0)
					{
						count++;
					}
				}
			}
			return count;
		}
		void FirstGeneration()
		{
			srand(time(NULL));
			for (int x = 0;x < cols;x++)
			{
				for (int y = 0;y < rows;y++)
				{
					this->field[x][y] = rand() % (int)nudDensity->Value == 0;
				}
			}
		}
		void NextGeneration()
		{
			RenderActivity = true;
			СountingGeneration++;
			int NumberOfNeighbors;
			bool ExistenceOfLife;
			for (int x = 0;x < cols;x++)
			{
				for (int y = 0;y < rows;y++)
				{
					NumberOfNeighbors = СountingNeighbors(x, y);
					ExistenceOfLife = this->field[x][y];
					if (ExistenceOfLife == 0 && NumberOfNeighbors == 3)
					{
						this->newfield[x][y] = true;
						this->graphics->FillRectangle(Brushes::Red, x * resolution, y * resolution, resolution - 1, resolution - 1);
					}
					else if (ExistenceOfLife == 1 && (NumberOfNeighbors > 3 || NumberOfNeighbors < 2))
					{
						this->newfield[x][y] = false;
						this->graphics->FillRectangle(Brushes::White, x * resolution, y * resolution, resolution - 1, resolution - 1);
					}
					else
					{
						this->newfield[x][y] = this->field[x][y];
					}
				}
			}
			this->field = this->newfield;
			RenderActivity = false;
		}
		void StartGame()
		{
			if (timer->Enabled)
			{
				return;
			}
			СountingGeneration = 0;
			nudResolution->Enabled = false;
			nudDensity->Enabled = false;
			resolution = (int)nudResolution->Value;
			this->rows = static_cast<int>(pictureBox->Height / resolution);
			this->cols = static_cast<int>(pictureBox->Width / resolution);
			field = new bool* [cols];
			for (int i = 0; i < cols; ++i)
				field[i] = new bool[rows];
			FirstGeneration();
			newfield = new bool* [cols];
			for (int i = 0; i < cols; ++i)
				newfield[i] = new bool[rows];
			pictureBox->Image = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			graphics = pictureBox->CreateGraphics();
			timer->Start();
		}
		void StopGame()
		{
			if (!(timer->Enabled))
			{
				return;
			}
			else
			{
				timer->Stop();
				nudResolution->Enabled = true;
				nudDensity->Enabled = true;
				СountingGeneration = 0;
				pictureBox->Refresh();
			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::NumericUpDown^ nudResolution;
	protected:


	private: System::Windows::Forms::Label^ Resolution;
	private: System::Windows::Forms::Button^ StartProgram;


	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::Timer^ timer;

	private: System::Windows::Forms::Label^ Density;
	private: System::Windows::Forms::NumericUpDown^ nudDensity;
	private: System::Windows::Forms::Button^ FinishProgram;


	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->NextIteration = (gcnew System::Windows::Forms::Button());
			this->FinishProgram = (gcnew System::Windows::Forms::Button());
			this->nudDensity = (gcnew System::Windows::Forms::NumericUpDown());
			this->Density = (gcnew System::Windows::Forms::Label());
			this->nudResolution = (gcnew System::Windows::Forms::NumericUpDown());
			this->Resolution = (gcnew System::Windows::Forms::Label());
			this->StartProgram = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudDensity))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudResolution))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->NextIteration);
			this->splitContainer1->Panel1->Controls->Add(this->FinishProgram);
			this->splitContainer1->Panel1->Controls->Add(this->nudDensity);
			this->splitContainer1->Panel1->Controls->Add(this->Density);
			this->splitContainer1->Panel1->Controls->Add(this->nudResolution);
			this->splitContainer1->Panel1->Controls->Add(this->Resolution);
			this->splitContainer1->Panel1->Controls->Add(this->StartProgram);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->pictureBox);
			this->splitContainer1->Size = System::Drawing::Size(784, 361);
			this->splitContainer1->SplitterDistance = 144;
			this->splitContainer1->TabIndex = 0;
			// 
			// NextIteration
			// 
			this->NextIteration->Location = System::Drawing::Point(12, 148);
			this->NextIteration->Name = L"NextIteration";
			this->NextIteration->Size = System::Drawing::Size(120, 23);
			this->NextIteration->TabIndex = 7;
			this->NextIteration->Text = L"Next iteration";
			this->NextIteration->UseVisualStyleBackColor = true;
			this->NextIteration->Click += gcnew System::EventHandler(this, &MyForm::NextIteration_Click);
			// 
			// FinishProgram
			// 
			this->FinishProgram->Location = System::Drawing::Point(12, 119);
			this->FinishProgram->Name = L"FinishProgram";
			this->FinishProgram->Size = System::Drawing::Size(120, 23);
			this->FinishProgram->TabIndex = 6;
			this->FinishProgram->Text = L"Finish program";
			this->FinishProgram->UseVisualStyleBackColor = true;
			this->FinishProgram->Click += gcnew System::EventHandler(this, &MyForm::FinishProgram_Click);
			// 
			// nudDensity
			// 
			this->nudDensity->Location = System::Drawing::Point(12, 64);
			this->nudDensity->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			this->nudDensity->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->nudDensity->Name = L"nudDensity";
			this->nudDensity->Size = System::Drawing::Size(120, 20);
			this->nudDensity->TabIndex = 5;
			this->nudDensity->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// Density
			// 
			this->Density->AutoSize = true;
			this->Density->Location = System::Drawing::Point(12, 48);
			this->Density->Name = L"Density";
			this->Density->Size = System::Drawing::Size(42, 13);
			this->Density->TabIndex = 4;
			this->Density->Text = L"Density";
			// 
			// nudResolution
			// 
			this->nudResolution->Location = System::Drawing::Point(12, 25);
			this->nudResolution->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			this->nudResolution->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->nudResolution->Name = L"nudResolution";
			this->nudResolution->Size = System::Drawing::Size(120, 20);
			this->nudResolution->TabIndex = 3;
			this->nudResolution->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// Resolution
			// 
			this->Resolution->AutoSize = true;
			this->Resolution->Location = System::Drawing::Point(12, 9);
			this->Resolution->Name = L"Resolution";
			this->Resolution->Size = System::Drawing::Size(57, 13);
			this->Resolution->TabIndex = 1;
			this->Resolution->Text = L"Resolution";
			// 
			// StartProgram
			// 
			this->StartProgram->Location = System::Drawing::Point(12, 90);
			this->StartProgram->Name = L"StartProgram";
			this->StartProgram->Size = System::Drawing::Size(120, 23);
			this->StartProgram->TabIndex = 0;
			this->StartProgram->Text = L"Start program";
			this->StartProgram->UseVisualStyleBackColor = true;
			this->StartProgram->Click += gcnew System::EventHandler(this, &MyForm::StartProgram_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->BackColor = System::Drawing::Color::White;
			this->pictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(636, 361);
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->pictureBox->WaitOnLoad = true;
			this->pictureBox->Click += gcnew System::EventHandler(this, &MyForm::StartProgram_Click);
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox_Paint);
			this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox_MouseMove);
			// 
			// timer
			// 
			this->timer->Interval = 50;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 361);
			this->Controls->Add(this->splitContainer1);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->Text = L"Life Simulation";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudDensity))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudResolution))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (RenderActivity == false)
			NextGeneration();
	}
	private: System::Void StartProgram_Click(System::Object^ sender, System::EventArgs^ e) {
		StartGame();
	}
	private: System::Void FinishProgram_Click(System::Object^ sender, System::EventArgs^ e) {
		StopGame();
	}
	private: System::Void pictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pictureBox_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (timer->Enabled)
		{

			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				int x = e->Location.X / resolution;
				int y = e->Location.Y / resolution;
				if (ValidateMousePosition(x, y) == 1)
				{
					field[x][y] = true;
				}
			}
			if (e->Button == System::Windows::Forms::MouseButtons::Right)
			{
				int x = e->Location.X / resolution;
				int y = e->Location.Y / resolution;
				if (ValidateMousePosition(x, y) == 1)
				{
					field[x][y] = false;
				}
			}
		}
	}
	private: System::Void NextIteration_Click(System::Object^ sender, System::EventArgs^ e) {
		if (RenderActivity == false)
			NextGeneration();
	}
	};
}
