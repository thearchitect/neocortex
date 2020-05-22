#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Neocortex {

	/// <summary>
	/// Summary for SegmentationProperties
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class SegmentationProperties : public System::Windows::Forms::Form
	{
	public:
		SegmentationProperties(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			IsSnakeSegmentation = false;
			IsDensityCoords = false;
			IsClustersCoords = false;
			IsConnectedRegions = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SegmentationProperties()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::CheckBox^  CheckBox_DensityCoords;
	public: System::Windows::Forms::CheckBox^  CheckBox_ClustersCoords;

	public: System::Windows::Forms::CheckBox^  CheckBox_ConnectedRegions;

	public: bool IsSnakeSegmentation;	// сегментировать/не сегментировать области, найденные методом активного контура
	public: bool IsDensityCoords;		// учитывать/не учитывать координаты при сегментации по плотности
	public: bool IsClustersCoords;		// кластеризовать/не кластеризовать найденные сегменты по координатам
	public: bool IsConnectedRegions;	// искать/не искать связные области в сегментах

	private: System::Windows::Forms::Button^  Button_Accept;
	private: System::Windows::Forms::Button^  Button_Cancel;
	private: System::Windows::Forms::TabControl^  TabControl_Options;

	private: System::Windows::Forms::TabPage^  TabPage_Common;
	private: System::Windows::Forms::TabPage^  TabPage_Filtering;
	private: System::Windows::Forms::TabPage^  TabPage_Matching;
	public: System::Windows::Forms::CheckBox^  CheckBox_MeanXY;
	private: 
	public: System::Windows::Forms::CheckBox^  CheckBox_Histogram;
	public: System::Windows::Forms::CheckBox^  CheckBox_DensityDeviation;
	public: System::Windows::Forms::CheckBox^  CheckBox_MeanDensity;










	public: System::Windows::Forms::CheckBox^  CheckBox_DevY;
	private: 
	public: System::Windows::Forms::CheckBox^  CheckBox_DevX;
	public: System::Windows::Forms::CheckBox^  CheckBox_Volume;









	private: System::Windows::Forms::GroupBox^  GroupBox_SegmentsAdjacence;
	private: System::Windows::Forms::RadioButton^  RadioButton_Neighbours;



	private: System::Windows::Forms::RadioButton^  RadioButton_EveryEvery;
	private: System::Windows::Forms::RadioButton^  RadioButton_NotUsed;


	private: System::Windows::Forms::Label^  Label_MaskWidth;
	private: System::Windows::Forms::NumericUpDown^  NumericUpDown_MaskWidth;
	private: System::Windows::Forms::Label^  Label_MaskHeight;



	private: System::Windows::Forms::NumericUpDown^  NumericUpDown_MaskHeight;
	public: System::Windows::Forms::TrackBar^  TrackBar_IterationsCount;
	private: 

	public: System::Windows::Forms::Label^  Label_IterationsCount;
	private: 
	public: System::Windows::Forms::Label^  Label_SegmentsCount;
	public: System::Windows::Forms::TrackBar^  TrackBar_SegmentsCount;






	private: System::Windows::Forms::GroupBox^  GroupBoxAlgorithm;
	public: System::Windows::Forms::RadioButton^  RadioButton_Consequtive;
	private: 
	public: System::Windows::Forms::RadioButton^  RadioButton_GPU;


public: System::Windows::Forms::CheckBox^  CheckBox_SnakeSegmentation;
private: 

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  GroupBoxDiapason;
	public: System::Windows::Forms::TextBox^  TextBox_HighBorder;
	private: 
	public: System::Windows::Forms::TextBox^  TextBox_LowBorder;


	private: System::Windows::Forms::Label^  Label_HighBorder;
	private: System::Windows::Forms::Label^  Label_LowBorder;
public: System::Windows::Forms::Label^  Label_SubClustersCount;
public: System::Windows::Forms::TrackBar^  TrackBar_SubClustersCount;
private: 








	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CheckBox_DensityCoords = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_ClustersCoords = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_ConnectedRegions = (gcnew System::Windows::Forms::CheckBox());
			this->Button_Accept = (gcnew System::Windows::Forms::Button());
			this->Button_Cancel = (gcnew System::Windows::Forms::Button());
			this->TabControl_Options = (gcnew System::Windows::Forms::TabControl());
			this->TabPage_Common = (gcnew System::Windows::Forms::TabPage());
			this->Label_SubClustersCount = (gcnew System::Windows::Forms::Label());
			this->TrackBar_SubClustersCount = (gcnew System::Windows::Forms::TrackBar());
			this->GroupBoxDiapason = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox_HighBorder = (gcnew System::Windows::Forms::TextBox());
			this->TextBox_LowBorder = (gcnew System::Windows::Forms::TextBox());
			this->Label_HighBorder = (gcnew System::Windows::Forms::Label());
			this->Label_LowBorder = (gcnew System::Windows::Forms::Label());
			this->CheckBox_SnakeSegmentation = (gcnew System::Windows::Forms::CheckBox());
			this->GroupBoxAlgorithm = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_Consequtive = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_GPU = (gcnew System::Windows::Forms::RadioButton());
			this->TrackBar_IterationsCount = (gcnew System::Windows::Forms::TrackBar());
			this->Label_IterationsCount = (gcnew System::Windows::Forms::Label());
			this->Label_SegmentsCount = (gcnew System::Windows::Forms::Label());
			this->TrackBar_SegmentsCount = (gcnew System::Windows::Forms::TrackBar());
			this->TabPage_Filtering = (gcnew System::Windows::Forms::TabPage());
			this->Label_MaskHeight = (gcnew System::Windows::Forms::Label());
			this->NumericUpDown_MaskHeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->Label_MaskWidth = (gcnew System::Windows::Forms::Label());
			this->NumericUpDown_MaskWidth = (gcnew System::Windows::Forms::NumericUpDown());
			this->TabPage_Matching = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->CheckBox_DensityDeviation = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_Volume = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_MeanXY = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_DevX = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_DevY = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_Histogram = (gcnew System::Windows::Forms::CheckBox());
			this->CheckBox_MeanDensity = (gcnew System::Windows::Forms::CheckBox());
			this->GroupBox_SegmentsAdjacence = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_NotUsed = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_Neighbours = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_EveryEvery = (gcnew System::Windows::Forms::RadioButton());
			this->TabControl_Options->SuspendLayout();
			this->TabPage_Common->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_SubClustersCount))->BeginInit();
			this->GroupBoxDiapason->SuspendLayout();
			this->GroupBoxAlgorithm->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_SegmentsCount))->BeginInit();
			this->TabPage_Filtering->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_MaskHeight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_MaskWidth))->BeginInit();
			this->TabPage_Matching->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->GroupBox_SegmentsAdjacence->SuspendLayout();
			this->SuspendLayout();
			// 
			// CheckBox_DensityCoords
			// 
			this->CheckBox_DensityCoords->AutoSize = true;
			this->CheckBox_DensityCoords->Location = System::Drawing::Point(58, 57);
			this->CheckBox_DensityCoords->Name = L"CheckBox_DensityCoords";
			this->CheckBox_DensityCoords->Size = System::Drawing::Size(301, 21);
			this->CheckBox_DensityCoords->TabIndex = 0;
			this->CheckBox_DensityCoords->Text = L"Учитывать координаты при сегментации";
			this->CheckBox_DensityCoords->UseVisualStyleBackColor = true;
			// 
			// CheckBox_ClustersCoords
			// 
			this->CheckBox_ClustersCoords->AutoSize = true;
			this->CheckBox_ClustersCoords->Location = System::Drawing::Point(58, 97);
			this->CheckBox_ClustersCoords->Name = L"CheckBox_ClustersCoords";
			this->CheckBox_ClustersCoords->Size = System::Drawing::Size(315, 21);
			this->CheckBox_ClustersCoords->TabIndex = 1;
			this->CheckBox_ClustersCoords->Text = L"Сегментировать кластеры по координатам";
			this->CheckBox_ClustersCoords->UseVisualStyleBackColor = true;
			// 
			// CheckBox_ConnectedRegions
			// 
			this->CheckBox_ConnectedRegions->AutoSize = true;
			this->CheckBox_ConnectedRegions->Location = System::Drawing::Point(58, 137);
			this->CheckBox_ConnectedRegions->Name = L"CheckBox_ConnectedRegions";
			this->CheckBox_ConnectedRegions->Size = System::Drawing::Size(274, 21);
			this->CheckBox_ConnectedRegions->TabIndex = 3;
			this->CheckBox_ConnectedRegions->Text = L"Поиск связных областей в сегментах";
			this->CheckBox_ConnectedRegions->UseVisualStyleBackColor = true;
			// 
			// Button_Accept
			// 
			this->Button_Accept->Location = System::Drawing::Point(153, 511);
			this->Button_Accept->Name = L"Button_Accept";
			this->Button_Accept->Size = System::Drawing::Size(90, 38);
			this->Button_Accept->TabIndex = 4;
			this->Button_Accept->Text = L"Применить";
			this->Button_Accept->UseVisualStyleBackColor = true;
			this->Button_Accept->Click += gcnew System::EventHandler(this, &SegmentationProperties::Button_Accept_Click);
			// 
			// Button_Cancel
			// 
			this->Button_Cancel->Location = System::Drawing::Point(313, 511);
			this->Button_Cancel->Name = L"Button_Cancel";
			this->Button_Cancel->Size = System::Drawing::Size(90, 38);
			this->Button_Cancel->TabIndex = 5;
			this->Button_Cancel->Text = L"Отмена";
			this->Button_Cancel->UseVisualStyleBackColor = true;
			this->Button_Cancel->Click += gcnew System::EventHandler(this, &SegmentationProperties::Button_Cancel_Click);
			// 
			// TabControl_Options
			// 
			this->TabControl_Options->Controls->Add(this->TabPage_Common);
			this->TabControl_Options->Controls->Add(this->TabPage_Filtering);
			this->TabControl_Options->Controls->Add(this->TabPage_Matching);
			this->TabControl_Options->Location = System::Drawing::Point(0, 0);
			this->TabControl_Options->Name = L"TabControl_Options";
			this->TabControl_Options->SelectedIndex = 0;
			this->TabControl_Options->Size = System::Drawing::Size(578, 503);
			this->TabControl_Options->TabIndex = 6;
			// 
			// TabPage_Common
			// 
			this->TabPage_Common->BackColor = System::Drawing::SystemColors::Control;
			this->TabPage_Common->Controls->Add(this->Label_SubClustersCount);
			this->TabPage_Common->Controls->Add(this->TrackBar_SubClustersCount);
			this->TabPage_Common->Controls->Add(this->GroupBoxDiapason);
			this->TabPage_Common->Controls->Add(this->CheckBox_SnakeSegmentation);
			this->TabPage_Common->Controls->Add(this->GroupBoxAlgorithm);
			this->TabPage_Common->Controls->Add(this->TrackBar_IterationsCount);
			this->TabPage_Common->Controls->Add(this->Label_IterationsCount);
			this->TabPage_Common->Controls->Add(this->Label_SegmentsCount);
			this->TabPage_Common->Controls->Add(this->TrackBar_SegmentsCount);
			this->TabPage_Common->Controls->Add(this->CheckBox_DensityCoords);
			this->TabPage_Common->Controls->Add(this->CheckBox_ClustersCoords);
			this->TabPage_Common->Controls->Add(this->CheckBox_ConnectedRegions);
			this->TabPage_Common->Location = System::Drawing::Point(4, 25);
			this->TabPage_Common->Name = L"TabPage_Common";
			this->TabPage_Common->Padding = System::Windows::Forms::Padding(3);
			this->TabPage_Common->Size = System::Drawing::Size(570, 474);
			this->TabPage_Common->TabIndex = 0;
			this->TabPage_Common->Text = L"Общие";
			// 
			// Label_SubClustersCount
			// 
			this->Label_SubClustersCount->AutoSize = true;
			this->Label_SubClustersCount->Location = System::Drawing::Point(55, 314);
			this->Label_SubClustersCount->Name = L"Label_SubClustersCount";
			this->Label_SubClustersCount->Size = System::Drawing::Size(248, 17);
			this->Label_SubClustersCount->TabIndex = 24;
			this->Label_SubClustersCount->Text = L"Максимальное число подкластеров:";
			// 
			// TrackBar_SubClustersCount
			// 
			this->TrackBar_SubClustersCount->Location = System::Drawing::Point(353, 309);
			this->TrackBar_SubClustersCount->Maximum = 50;
			this->TrackBar_SubClustersCount->Minimum = 2;
			this->TrackBar_SubClustersCount->Name = L"TrackBar_SubClustersCount";
			this->TrackBar_SubClustersCount->Size = System::Drawing::Size(140, 56);
			this->TrackBar_SubClustersCount->TabIndex = 23;
			this->TrackBar_SubClustersCount->Value = 10;
			// 
			// GroupBoxDiapason
			// 
			this->GroupBoxDiapason->Controls->Add(this->TextBox_HighBorder);
			this->GroupBoxDiapason->Controls->Add(this->TextBox_LowBorder);
			this->GroupBoxDiapason->Controls->Add(this->Label_HighBorder);
			this->GroupBoxDiapason->Controls->Add(this->Label_LowBorder);
			this->GroupBoxDiapason->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->GroupBoxDiapason->Location = System::Drawing::Point(58, 171);
			this->GroupBoxDiapason->Name = L"GroupBoxDiapason";
			this->GroupBoxDiapason->Size = System::Drawing::Size(430, 79);
			this->GroupBoxDiapason->TabIndex = 22;
			this->GroupBoxDiapason->TabStop = false;
			this->GroupBoxDiapason->Text = L"Диапазон значений плотности";
			// 
			// TextBox_HighBorder
			// 
			this->TextBox_HighBorder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TextBox_HighBorder->Location = System::Drawing::Point(359, 36);
			this->TextBox_HighBorder->Name = L"TextBox_HighBorder";
			this->TextBox_HighBorder->Size = System::Drawing::Size(52, 22);
			this->TextBox_HighBorder->TabIndex = 4;
			// 
			// TextBox_LowBorder
			// 
			this->TextBox_LowBorder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TextBox_LowBorder->Location = System::Drawing::Point(150, 36);
			this->TextBox_LowBorder->Name = L"TextBox_LowBorder";
			this->TextBox_LowBorder->Size = System::Drawing::Size(52, 22);
			this->TextBox_LowBorder->TabIndex = 3;
			// 
			// Label_HighBorder
			// 
			this->Label_HighBorder->AutoSize = true;
			this->Label_HighBorder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->Label_HighBorder->Location = System::Drawing::Point(217, 38);
			this->Label_HighBorder->Name = L"Label_HighBorder";
			this->Label_HighBorder->Size = System::Drawing::Size(124, 17);
			this->Label_HighBorder->TabIndex = 1;
			this->Label_HighBorder->Text = L"Верхняя граница:";
			// 
			// Label_LowBorder
			// 
			this->Label_LowBorder->AutoSize = true;
			this->Label_LowBorder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->Label_LowBorder->Location = System::Drawing::Point(13, 38);
			this->Label_LowBorder->Name = L"Label_LowBorder";
			this->Label_LowBorder->Size = System::Drawing::Size(120, 17);
			this->Label_LowBorder->TabIndex = 0;
			this->Label_LowBorder->Text = L"Нижняя граница:";
			// 
			// CheckBox_SnakeSegmentation
			// 
			this->CheckBox_SnakeSegmentation->AutoSize = true;
			this->CheckBox_SnakeSegmentation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->CheckBox_SnakeSegmentation->Location = System::Drawing::Point(58, 17);
			this->CheckBox_SnakeSegmentation->Name = L"CheckBox_SnakeSegmentation";
			this->CheckBox_SnakeSegmentation->Size = System::Drawing::Size(465, 21);
			this->CheckBox_SnakeSegmentation->TabIndex = 21;
			this->CheckBox_SnakeSegmentation->Text = L"Сегментировать области, найденные методом активного контура";
			this->CheckBox_SnakeSegmentation->UseVisualStyleBackColor = true;
			// 
			// GroupBoxAlgorithm
			// 
			this->GroupBoxAlgorithm->Controls->Add(this->RadioButton_Consequtive);
			this->GroupBoxAlgorithm->Controls->Add(this->RadioButton_GPU);
			this->GroupBoxAlgorithm->Location = System::Drawing::Point(62, 406);
			this->GroupBoxAlgorithm->Name = L"GroupBoxAlgorithm";
			this->GroupBoxAlgorithm->Size = System::Drawing::Size(430, 61);
			this->GroupBoxAlgorithm->TabIndex = 12;
			this->GroupBoxAlgorithm->TabStop = false;
			this->GroupBoxAlgorithm->Text = L"Алгоритм сегментации";
			// 
			// RadioButton_Consequtive
			// 
			this->RadioButton_Consequtive->AutoSize = true;
			this->RadioButton_Consequtive->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->RadioButton_Consequtive->Location = System::Drawing::Point(19, 27);
			this->RadioButton_Consequtive->Name = L"RadioButton_Consequtive";
			this->RadioButton_Consequtive->Size = System::Drawing::Size(155, 21);
			this->RadioButton_Consequtive->TabIndex = 8;
			this->RadioButton_Consequtive->Text = L"последовательный";
			this->RadioButton_Consequtive->UseVisualStyleBackColor = true;
			// 
			// RadioButton_GPU
			// 
			this->RadioButton_GPU->AutoSize = true;
			this->RadioButton_GPU->Checked = true;
			this->RadioButton_GPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->RadioButton_GPU->Location = System::Drawing::Point(206, 27);
			this->RadioButton_GPU->Name = L"RadioButton_GPU";
			this->RadioButton_GPU->Size = System::Drawing::Size(188, 21);
			this->RadioButton_GPU->TabIndex = 9;
			this->RadioButton_GPU->TabStop = true;
			this->RadioButton_GPU->Text = L"параллельный для GPU";
			this->RadioButton_GPU->UseVisualStyleBackColor = true;
			// 
			// TrackBar_IterationsCount
			// 
			this->TrackBar_IterationsCount->Location = System::Drawing::Point(353, 362);
			this->TrackBar_IterationsCount->Maximum = 50;
			this->TrackBar_IterationsCount->Minimum = 1;
			this->TrackBar_IterationsCount->Name = L"TrackBar_IterationsCount";
			this->TrackBar_IterationsCount->Size = System::Drawing::Size(140, 56);
			this->TrackBar_IterationsCount->TabIndex = 11;
			this->TrackBar_IterationsCount->Value = 10;
			this->TrackBar_IterationsCount->ValueChanged += gcnew System::EventHandler(this, &SegmentationProperties::TrackBar_IterationsCount_ValueChanged);
			// 
			// Label_IterationsCount
			// 
			this->Label_IterationsCount->AutoSize = true;
			this->Label_IterationsCount->Location = System::Drawing::Point(71, 366);
			this->Label_IterationsCount->Name = L"Label_IterationsCount";
			this->Label_IterationsCount->Size = System::Drawing::Size(230, 17);
			this->Label_IterationsCount->TabIndex = 10;
			this->Label_IterationsCount->Text = L"Количество итераций алгоритма:";
			// 
			// Label_SegmentsCount
			// 
			this->Label_SegmentsCount->AutoSize = true;
			this->Label_SegmentsCount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->Label_SegmentsCount->Location = System::Drawing::Point(80, 265);
			this->Label_SegmentsCount->Name = L"Label_SegmentsCount";
			this->Label_SegmentsCount->Size = System::Drawing::Size(223, 17);
			this->Label_SegmentsCount->TabIndex = 8;
			this->Label_SegmentsCount->Text = L"Максимальное число сегментов:";
			// 
			// TrackBar_SegmentsCount
			// 
			this->TrackBar_SegmentsCount->Location = System::Drawing::Point(353, 259);
			this->TrackBar_SegmentsCount->Maximum = 50;
			this->TrackBar_SegmentsCount->Minimum = 2;
			this->TrackBar_SegmentsCount->Name = L"TrackBar_SegmentsCount";
			this->TrackBar_SegmentsCount->Size = System::Drawing::Size(140, 56);
			this->TrackBar_SegmentsCount->TabIndex = 9;
			this->TrackBar_SegmentsCount->Value = 10;
			this->TrackBar_SegmentsCount->ValueChanged += gcnew System::EventHandler(this, &SegmentationProperties::TrackBar_SegmentsCount_ValueChanged);
			// 
			// TabPage_Filtering
			// 
			this->TabPage_Filtering->BackColor = System::Drawing::SystemColors::Control;
			this->TabPage_Filtering->Controls->Add(this->Label_MaskHeight);
			this->TabPage_Filtering->Controls->Add(this->NumericUpDown_MaskHeight);
			this->TabPage_Filtering->Controls->Add(this->Label_MaskWidth);
			this->TabPage_Filtering->Controls->Add(this->NumericUpDown_MaskWidth);
			this->TabPage_Filtering->Location = System::Drawing::Point(4, 25);
			this->TabPage_Filtering->Name = L"TabPage_Filtering";
			this->TabPage_Filtering->Padding = System::Windows::Forms::Padding(3);
			this->TabPage_Filtering->Size = System::Drawing::Size(570, 474);
			this->TabPage_Filtering->TabIndex = 1;
			this->TabPage_Filtering->Text = L"Фильтрация сегментов";
			// 
			// Label_MaskHeight
			// 
			this->Label_MaskHeight->AutoSize = true;
			this->Label_MaskHeight->Location = System::Drawing::Point(303, 34);
			this->Label_MaskHeight->Name = L"Label_MaskHeight";
			this->Label_MaskHeight->Size = System::Drawing::Size(104, 17);
			this->Label_MaskHeight->TabIndex = 3;
			this->Label_MaskHeight->Text = L"Высота маски:";
			// 
			// NumericUpDown_MaskHeight
			// 
			this->NumericUpDown_MaskHeight->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->NumericUpDown_MaskHeight->Location = System::Drawing::Point(409, 32);
			this->NumericUpDown_MaskHeight->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
			this->NumericUpDown_MaskHeight->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->NumericUpDown_MaskHeight->Name = L"NumericUpDown_MaskHeight";
			this->NumericUpDown_MaskHeight->Size = System::Drawing::Size(40, 22);
			this->NumericUpDown_MaskHeight->TabIndex = 2;
			this->NumericUpDown_MaskHeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			// 
			// Label_MaskWidth
			// 
			this->Label_MaskWidth->AutoSize = true;
			this->Label_MaskWidth->Location = System::Drawing::Point(106, 34);
			this->Label_MaskWidth->Name = L"Label_MaskWidth";
			this->Label_MaskWidth->Size = System::Drawing::Size(106, 17);
			this->Label_MaskWidth->TabIndex = 1;
			this->Label_MaskWidth->Text = L"Ширина маски:";
			// 
			// NumericUpDown_MaskWidth
			// 
			this->NumericUpDown_MaskWidth->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->NumericUpDown_MaskWidth->Location = System::Drawing::Point(214, 32);
			this->NumericUpDown_MaskWidth->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
			this->NumericUpDown_MaskWidth->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->NumericUpDown_MaskWidth->Name = L"NumericUpDown_MaskWidth";
			this->NumericUpDown_MaskWidth->Size = System::Drawing::Size(40, 22);
			this->NumericUpDown_MaskWidth->TabIndex = 0;
			this->NumericUpDown_MaskWidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			// 
			// TabPage_Matching
			// 
			this->TabPage_Matching->BackColor = System::Drawing::SystemColors::Control;
			this->TabPage_Matching->Controls->Add(this->groupBox1);
			this->TabPage_Matching->Controls->Add(this->GroupBox_SegmentsAdjacence);
			this->TabPage_Matching->Location = System::Drawing::Point(4, 25);
			this->TabPage_Matching->Name = L"TabPage_Matching";
			this->TabPage_Matching->Padding = System::Windows::Forms::Padding(3);
			this->TabPage_Matching->Size = System::Drawing::Size(570, 474);
			this->TabPage_Matching->TabIndex = 2;
			this->TabPage_Matching->Text = L"Поиск соответствий";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->CheckBox_DensityDeviation);
			this->groupBox1->Controls->Add(this->CheckBox_Volume);
			this->groupBox1->Controls->Add(this->CheckBox_MeanXY);
			this->groupBox1->Controls->Add(this->CheckBox_DevX);
			this->groupBox1->Controls->Add(this->CheckBox_DevY);
			this->groupBox1->Controls->Add(this->CheckBox_Histogram);
			this->groupBox1->Controls->Add(this->CheckBox_MeanDensity);
			this->groupBox1->Location = System::Drawing::Point(6, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(305, 304);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Используемые атрибуты сегмента:";
			// 
			// CheckBox_DensityDeviation
			// 
			this->CheckBox_DensityDeviation->AutoSize = true;
			this->CheckBox_DensityDeviation->Location = System::Drawing::Point(17, 106);
			this->CheckBox_DensityDeviation->Name = L"CheckBox_DensityDeviation";
			this->CheckBox_DensityDeviation->Size = System::Drawing::Size(176, 21);
			this->CheckBox_DensityDeviation->TabIndex = 3;
			this->CheckBox_DensityDeviation->Text = L"Дисперсия плотности";
			this->CheckBox_DensityDeviation->UseVisualStyleBackColor = true;
			// 
			// CheckBox_Volume
			// 
			this->CheckBox_Volume->AutoSize = true;
			this->CheckBox_Volume->Location = System::Drawing::Point(17, 217);
			this->CheckBox_Volume->Name = L"CheckBox_Volume";
			this->CheckBox_Volume->Size = System::Drawing::Size(75, 21);
			this->CheckBox_Volume->TabIndex = 7;
			this->CheckBox_Volume->Text = L"Объём";
			this->CheckBox_Volume->UseVisualStyleBackColor = true;
			// 
			// CheckBox_MeanXY
			// 
			this->CheckBox_MeanXY->AutoSize = true;
			this->CheckBox_MeanXY->Location = System::Drawing::Point(17, 142);
			this->CheckBox_MeanXY->Name = L"CheckBox_MeanXY";
			this->CheckBox_MeanXY->Size = System::Drawing::Size(218, 21);
			this->CheckBox_MeanXY->TabIndex = 1;
			this->CheckBox_MeanXY->Text = L"Геометрический центр масс";
			this->CheckBox_MeanXY->UseVisualStyleBackColor = true;
			// 
			// CheckBox_DevX
			// 
			this->CheckBox_DevX->AutoSize = true;
			this->CheckBox_DevX->Location = System::Drawing::Point(17, 180);
			this->CheckBox_DevX->Name = L"CheckBox_DevX";
			this->CheckBox_DevX->Size = System::Drawing::Size(136, 21);
			this->CheckBox_DevX->TabIndex = 4;
			this->CheckBox_DevX->Text = L"Дисперсия по X";
			this->CheckBox_DevX->UseVisualStyleBackColor = true;
			// 
			// CheckBox_DevY
			// 
			this->CheckBox_DevY->AutoSize = true;
			this->CheckBox_DevY->Location = System::Drawing::Point(159, 180);
			this->CheckBox_DevY->Name = L"CheckBox_DevY";
			this->CheckBox_DevY->Size = System::Drawing::Size(136, 21);
			this->CheckBox_DevY->TabIndex = 5;
			this->CheckBox_DevY->Text = L"Дисперсия по Y";
			this->CheckBox_DevY->UseVisualStyleBackColor = true;
			// 
			// CheckBox_Histogram
			// 
			this->CheckBox_Histogram->AutoSize = true;
			this->CheckBox_Histogram->Location = System::Drawing::Point(17, 34);
			this->CheckBox_Histogram->Name = L"CheckBox_Histogram";
			this->CheckBox_Histogram->Size = System::Drawing::Size(115, 21);
			this->CheckBox_Histogram->TabIndex = 0;
			this->CheckBox_Histogram->Text = L"Гистограмма";
			this->CheckBox_Histogram->UseVisualStyleBackColor = true;
			// 
			// CheckBox_MeanDensity
			// 
			this->CheckBox_MeanDensity->AutoSize = true;
			this->CheckBox_MeanDensity->Location = System::Drawing::Point(17, 70);
			this->CheckBox_MeanDensity->Name = L"CheckBox_MeanDensity";
			this->CheckBox_MeanDensity->Size = System::Drawing::Size(227, 21);
			this->CheckBox_MeanDensity->TabIndex = 2;
			this->CheckBox_MeanDensity->Text = L"Среднее значение плотности";
			this->CheckBox_MeanDensity->UseVisualStyleBackColor = true;
			// 
			// GroupBox_SegmentsAdjacence
			// 
			this->GroupBox_SegmentsAdjacence->Controls->Add(this->RadioButton_NotUsed);
			this->GroupBox_SegmentsAdjacence->Controls->Add(this->RadioButton_Neighbours);
			this->GroupBox_SegmentsAdjacence->Controls->Add(this->RadioButton_EveryEvery);
			this->GroupBox_SegmentsAdjacence->Location = System::Drawing::Point(317, 19);
			this->GroupBox_SegmentsAdjacence->Name = L"GroupBox_SegmentsAdjacence";
			this->GroupBox_SegmentsAdjacence->Size = System::Drawing::Size(247, 141);
			this->GroupBox_SegmentsAdjacence->TabIndex = 7;
			this->GroupBox_SegmentsAdjacence->TabStop = false;
			this->GroupBox_SegmentsAdjacence->Text = L"Смежность сегментов";
			// 
			// RadioButton_NotUsed
			// 
			this->RadioButton_NotUsed->AutoSize = true;
			this->RadioButton_NotUsed->Location = System::Drawing::Point(20, 106);
			this->RadioButton_NotUsed->Name = L"RadioButton_NotUsed";
			this->RadioButton_NotUsed->Size = System::Drawing::Size(120, 21);
			this->RadioButton_NotUsed->TabIndex = 2;
			this->RadioButton_NotUsed->TabStop = true;
			this->RadioButton_NotUsed->Text = L"Не учитывать";
			this->RadioButton_NotUsed->UseVisualStyleBackColor = true;
			// 
			// RadioButton_Neighbours
			// 
			this->RadioButton_Neighbours->AutoSize = true;
			this->RadioButton_Neighbours->Location = System::Drawing::Point(20, 68);
			this->RadioButton_Neighbours->Name = L"RadioButton_Neighbours";
			this->RadioButton_Neighbours->Size = System::Drawing::Size(201, 21);
			this->RadioButton_Neighbours->TabIndex = 1;
			this->RadioButton_Neighbours->TabStop = true;
			this->RadioButton_Neighbours->Text = L"Только на соседних слоях";
			this->RadioButton_Neighbours->UseVisualStyleBackColor = true;
			// 
			// RadioButton_EveryEvery
			// 
			this->RadioButton_EveryEvery->AutoSize = true;
			this->RadioButton_EveryEvery->Location = System::Drawing::Point(20, 32);
			this->RadioButton_EveryEvery->Name = L"RadioButton_EveryEvery";
			this->RadioButton_EveryEvery->Size = System::Drawing::Size(209, 21);
			this->RadioButton_EveryEvery->TabIndex = 0;
			this->RadioButton_EveryEvery->TabStop = true;
			this->RadioButton_EveryEvery->Text = L"Полная (каждый с каждым)";
			this->RadioButton_EveryEvery->UseVisualStyleBackColor = true;
			// 
			// SegmentationProperties
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(575, 557);
			this->Controls->Add(this->Button_Cancel);
			this->Controls->Add(this->TabControl_Options);
			this->Controls->Add(this->Button_Accept);
			this->Name = L"SegmentationProperties";
			this->Text = L"Neocortex - Настройки сегментации";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SegmentationProperties::SegmentationProperties_FormClosing);
			this->TabControl_Options->ResumeLayout(false);
			this->TabPage_Common->ResumeLayout(false);
			this->TabPage_Common->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_SubClustersCount))->EndInit();
			this->GroupBoxDiapason->ResumeLayout(false);
			this->GroupBoxDiapason->PerformLayout();
			this->GroupBoxAlgorithm->ResumeLayout(false);
			this->GroupBoxAlgorithm->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_IterationsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBar_SegmentsCount))->EndInit();
			this->TabPage_Filtering->ResumeLayout(false);
			this->TabPage_Filtering->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_MaskHeight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->NumericUpDown_MaskWidth))->EndInit();
			this->TabPage_Matching->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->GroupBox_SegmentsAdjacence->ResumeLayout(false);
			this->GroupBox_SegmentsAdjacence->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Button_Accept_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 IsSnakeSegmentation = this->CheckBox_SnakeSegmentation->Checked;
				 IsDensityCoords = this->CheckBox_DensityCoords->Checked;
				 IsClustersCoords = this->CheckBox_ClustersCoords->Checked;
				 IsConnectedRegions = this->CheckBox_ConnectedRegions->Checked;
				 Close();
			 }
private: System::Void SegmentationProperties_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 this->CheckBox_SnakeSegmentation->Checked = IsSnakeSegmentation;
			 this->CheckBox_DensityCoords->Checked = IsDensityCoords;
			 this->CheckBox_ClustersCoords->Checked = IsClustersCoords;
			 this->CheckBox_ConnectedRegions->Checked = IsConnectedRegions;
			 e->Cancel = true;
			 Hide();
		 }
private: System::Void Button_Cancel_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 Close();
		 }
private: System::Void TrackBar_SegmentsCount_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			this->Label_SegmentsCount->Text = L"Максимальное число сегментов: "+
				 this->TrackBar_SegmentsCount->Value;
		 }
private: System::Void TrackBar_IterationsCount_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Label_IterationsCount->Text = L"Количество итераций алгоритма: "+
				 this->TrackBar_IterationsCount->Value;
		 }
};
}
