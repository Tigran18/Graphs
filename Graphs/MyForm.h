#pragma once

namespace Graphs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBoxN;
	private: System::Windows::Forms::TableLayoutPanel^ AdjacencyMatrix;

	private: System::Windows::Forms::Button^ submit_btn1;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ theLongestPathAndInvestigationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ theShortestPathToolStripMenuItem;

	private: System::Windows::Forms::Button^ submit_btn2;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TableLayoutPanel^ IterationsTable;



	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ GraphsForm;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TableLayoutPanel^ SigmaTable;
	private: System::Windows::Forms::TableLayoutPanel^ DefTable;
	private: System::Windows::Forms::Label^ Rat_or_Not;
	private: System::Windows::Forms::Label^ label5;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxN = (gcnew System::Windows::Forms::TextBox());
			this->AdjacencyMatrix = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->submit_btn1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->theLongestPathAndInvestigationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->theShortestPathToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->submit_btn2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->IterationsTable = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->GraphsForm = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SigmaTable = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->DefTable = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->Rat_or_Not = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GraphsForm))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(20, 43);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(503, 25);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Enter the maximum number of tops or the name of the file\r\n";
			// 
			// textBoxN
			// 
			this->textBoxN->Location = System::Drawing::Point(534, 43);
			this->textBoxN->Margin = System::Windows::Forms::Padding(4);
			this->textBoxN->Name = L"textBoxN";
			this->textBoxN->Size = System::Drawing::Size(69, 22);
			this->textBoxN->TabIndex = 2;
			this->textBoxN->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBoxN_KeyDown);
			// 
			// AdjacencyMatrix
			// 
			this->AdjacencyMatrix->ColumnCount = 1;
			this->AdjacencyMatrix->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->AdjacencyMatrix->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->AdjacencyMatrix->Location = System::Drawing::Point(20, 111);
			this->AdjacencyMatrix->Margin = System::Windows::Forms::Padding(4);
			this->AdjacencyMatrix->Name = L"AdjacencyMatrix";
			this->AdjacencyMatrix->RowCount = 1;
			this->AdjacencyMatrix->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->AdjacencyMatrix->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->AdjacencyMatrix->Size = System::Drawing::Size(67, 62);
			this->AdjacencyMatrix->TabIndex = 3;
			// 
			// submit_btn1
			// 
			this->submit_btn1->BackColor = System::Drawing::Color::ForestGreen;
			this->submit_btn1->Location = System::Drawing::Point(611, 43);
			this->submit_btn1->Margin = System::Windows::Forms::Padding(4);
			this->submit_btn1->Name = L"submit_btn1";
			this->submit_btn1->Size = System::Drawing::Size(74, 28);
			this->submit_btn1->TabIndex = 0;
			this->submit_btn1->Text = L"V";
			this->submit_btn1->UseVisualStyleBackColor = false;
			this->submit_btn1->Click += gcnew System::EventHandler(this, &MyForm::submit_btn1_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->theLongestPathAndInvestigationToolStripMenuItem,
					this->theShortestPathToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1794, 28);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// theLongestPathAndInvestigationToolStripMenuItem
			// 
			this->theLongestPathAndInvestigationToolStripMenuItem->Name = L"theLongestPathAndInvestigationToolStripMenuItem";
			this->theLongestPathAndInvestigationToolStripMenuItem->Size = System::Drawing::Size(252, 24);
			this->theLongestPathAndInvestigationToolStripMenuItem->Text = L"The longest path and investigation";
			this->theLongestPathAndInvestigationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::theLongestPathAndInvestigationToolStripMenuItem_Click);
			// 
			// theShortestPathToolStripMenuItem
			// 
			this->theShortestPathToolStripMenuItem->Name = L"theShortestPathToolStripMenuItem";
			this->theShortestPathToolStripMenuItem->Size = System::Drawing::Size(137, 24);
			this->theShortestPathToolStripMenuItem->Text = L"The shortest path";
			this->theShortestPathToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::theShortestPathToolStripMenuItem_Click);
			// 
			// submit_btn2
			// 
			this->submit_btn2->AutoSize = true;
			this->submit_btn2->Location = System::Drawing::Point(588, 75);
			this->submit_btn2->Margin = System::Windows::Forms::Padding(4);
			this->submit_btn2->Name = L"submit_btn2";
			this->submit_btn2->Size = System::Drawing::Size(130, 30);
			this->submit_btn2->TabIndex = 5;
			this->submit_btn2->Text = L"0";
			this->submit_btn2->UseVisualStyleBackColor = true;
			this->submit_btn2->Click += gcnew System::EventHandler(this, &MyForm::submit_btn2_Click);
			this->submit_btn2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::submit_KeyDown);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(20, 74);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(249, 25);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Enter only 0 or 1 in the cells";
			// 
			// IterationsTable
			// 
			this->IterationsTable->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->IterationsTable->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::OutsetPartial;
			this->IterationsTable->ColumnCount = 1;
			this->IterationsTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->IterationsTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->IterationsTable->Location = System::Drawing::Point(20, 201);
			this->IterationsTable->Margin = System::Windows::Forms::Padding(4);
			this->IterationsTable->Name = L"IterationsTable";
			this->IterationsTable->RowCount = 1;
			this->IterationsTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->IterationsTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->IterationsTable->Size = System::Drawing::Size(67, 62);
			this->IterationsTable->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(20, 176);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(139, 25);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Total iterations";
			// 
			// GraphsForm
			// 
			this->GraphsForm->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->GraphsForm->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->GraphsForm->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"GraphsForm.InitialImage")));
			this->GraphsForm->Location = System::Drawing::Point(20, 295);
			this->GraphsForm->Margin = System::Windows::Forms::Padding(4);
			this->GraphsForm->Name = L"GraphsForm";
			this->GraphsForm->Size = System::Drawing::Size(666, 615);
			this->GraphsForm->TabIndex = 9;
			this->GraphsForm->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(20, 262);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(106, 25);
			this->label4->TabIndex = 10;
			this->label4->Text = L"The Graph";
			// 
			// SigmaTable
			// 
			this->SigmaTable->AutoSize = true;
			this->SigmaTable->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::InsetDouble;
			this->SigmaTable->ColumnCount = 1;
			this->SigmaTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SigmaTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SigmaTable->Location = System::Drawing::Point(693, 43);
			this->SigmaTable->Margin = System::Windows::Forms::Padding(4);
			this->SigmaTable->Name = L"SigmaTable";
			this->SigmaTable->RowCount = 1;
			this->SigmaTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SigmaTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->SigmaTable->Size = System::Drawing::Size(67, 62);
			this->SigmaTable->TabIndex = 11;
			// 
			// DefTable
			// 
			this->DefTable->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Outset;
			this->DefTable->ColumnCount = 1;
			this->DefTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->DefTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->DefTable->Location = System::Drawing::Point(20, 111);
			this->DefTable->Margin = System::Windows::Forms::Padding(4);
			this->DefTable->Name = L"DefTable";
			this->DefTable->RowCount = 1;
			this->DefTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->DefTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->DefTable->Size = System::Drawing::Size(67, 62);
			this->DefTable->TabIndex = 0;
			// 
			// Rat_or_Not
			// 
			this->Rat_or_Not->AutoSize = true;
			this->Rat_or_Not->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Rat_or_Not->Location = System::Drawing::Point(768, 33);
			this->Rat_or_Not->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->Rat_or_Not->Name = L"Rat_or_Not";
			this->Rat_or_Not->Size = System::Drawing::Size(95, 25);
			this->Rat_or_Not->TabIndex = 12;
			this->Rat_or_Not->Text = L"Rat or not";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(761, 262);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(126, 25);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Sigma Matrix";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(1815, 897);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->Rat_or_Not);
			this->Controls->Add(this->DefTable);
			this->Controls->Add(this->SigmaTable);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->GraphsForm);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->IterationsTable);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->submit_btn2);
			this->Controls->Add(this->submit_btn1);
			this->Controls->Add(this->AdjacencyMatrix);
			this->Controls->Add(this->textBoxN);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"Graphs";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GraphsForm))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: int size;

	private: array<Point>^ points;

	private: array<Point>^ points_for_vectors;

	private: void ClearData();

		   //My form

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);

	private: System::Void submit_btn1_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void submit_btn2_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void theLongestPathAndInvestigationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void textBoxN_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

	private: System::Void submit_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

	private: System::Void textBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);

	private: System::Void theShortestPathToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

		   //The longest path

	private: bool CheckTableContents1();

	private: void Matrix1(int** а, int** A);

	private: void SigmaMatrix(int iter_count, int** a, int** new_array);

	private: void DrawGraph(int** array1);

	private: void FindTheDefinitions(int** array1, int** new_array, int iter);

	private: void Iterations1(int iter_count, int** new_array);

		   //the shortest path

	private: bool CheckTableContents2();

	private: void Matrix2(int** а);

	private: void Iterations2(int** a, int** result);
	};
}