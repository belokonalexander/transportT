object TModuleForm: TTModuleForm
  Left = 0
  Top = 0
  Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1086#1073' '#1086#1090#1095#1077#1090#1077
  ClientHeight = 646
  ClientWidth = 1199
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 161
    Height = 605
    Align = alLeft
    Caption = 'Panel1'
    TabOrder = 0
    object MemoInfo: TMemo
      Left = 1
      Top = 1
      Width = 159
      Height = 603
      Align = alClient
      Enabled = False
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 605
    Width = 1199
    Height = 41
    Align = alBottom
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    ExplicitTop = 609
    object Label2: TLabel
      Left = 230
      Top = 14
      Width = 85
      Height = 13
      Caption = #1054#1073#1097#1080#1077' '#1079#1072#1090#1088#1072#1090#1099':'
    end
    object TotalSum: TLabel
      Left = 324
      Top = 14
      Width = 20
      Height = 13
      Caption = 'Sum'
    end
    object ReportRecieversButton: TSpeedButton
      AlignWithMargins = True
      Left = 533
      Top = 4
      Width = 161
      Height = 33
      Hint = '123'
      Align = alRight
      Caption = #1055#1086#1090#1088#1077#1073#1080#1090#1077#1083#1080
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHotLight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = ReportRecieversButtonClick
      ExplicitLeft = 408
      ExplicitTop = -1
      ExplicitHeight = 42
    end
    object ReportButton: TSpeedButton
      AlignWithMargins = True
      Left = 700
      Top = 4
      Width = 161
      Height = 33
      Hint = '123'
      Align = alRight
      Caption = #1054#1090#1095#1077#1090
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHotLight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = ReportButtonClick
      ExplicitLeft = 771
      ExplicitTop = 6
    end
    object Button1: TSpeedButton
      AlignWithMargins = True
      Left = 867
      Top = 4
      Width = 161
      Height = 33
      Hint = '123'
      Align = alRight
      Caption = #1055#1088#1077#1088#1074#1072#1090#1100
      Enabled = False
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHotLight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = Button1Click
      ExplicitLeft = 908
      ExplicitTop = 6
    end
    object ButtonStart: TSpeedButton
      AlignWithMargins = True
      Left = 1034
      Top = 4
      Width = 161
      Height = 33
      Hint = '123'
      Align = alRight
      Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHotLight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = ButtonStartClick
      ExplicitLeft = 1075
      ExplicitTop = 6
    end
    object ProgressBar1: TProgressBar
      Left = 7
      Top = 13
      Width = 209
      Height = 17
      TabOrder = 0
    end
  end
  object Panel3: TPanel
    Left = 161
    Top = 0
    Width = 1038
    Height = 605
    Align = alClient
    TabOrder = 2
    object ReportExists: TLabel
      AlignWithMargins = True
      Left = 4
      Top = 6
      Width = 1023
      Height = 19
      Margins.Top = 5
      Margins.Right = 10
      Align = alTop
      Alignment = taRightJustify
      AutoSize = False
      Caption = #1054#1090#1095#1077#1090' '#1087#1088#1080#1089#1091#1090#1089#1090#1074#1091#1077#1090' '#1074' '#1073#1072#1079#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -14
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitWidth = 669
    end
    object Panel5: TPanel
      Left = 1
      Top = 28
      Width = 1036
      Height = 576
      Align = alClient
      Caption = 'Panel5'
      TabOrder = 0
      object StringGrid1: TStringGrid
        Left = 1
        Top = 30
        Width = 1034
        Height = 545
        Align = alClient
        ColCount = 8
        DefaultColWidth = 128
        DrawingStyle = gdsGradient
        FixedCols = 0
        RowCount = 2
        GradientEndColor = clMenu
        ScrollBars = ssVertical
        TabOrder = 0
        ColWidths = (
          128
          128
          128
          128
          128
          128
          128
          128)
        RowHeights = (
          24
          24)
      end
      object Panel4: TPanel
        Left = 1
        Top = 1
        Width = 1034
        Height = 29
        Align = alTop
        TabOrder = 1
        object Label1: TLabel
          Left = 8
          Top = 8
          Width = 116
          Height = 13
          Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1090#1095#1077#1090#1072':'
        end
        object ReportName: TLabel
          Left = 135
          Top = 8
          Width = 112
          Height = 13
          Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1090#1095#1077#1090#1072
        end
        object ComboBox1: TComboBox
          AlignWithMargins = True
          Left = 885
          Top = 4
          Width = 145
          Height = 21
          Cursor = crHandPoint
          Align = alRight
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 0
          Text = #1053#1077#1090' '#1092#1080#1083#1100#1090#1088#1072
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1090' '#1092#1080#1083#1100#1090#1088#1072
            #1040#1075#1088#1077#1075#1072#1094#1080#1103' '#1087#1086' '#1088#1077#1075#1080#1086#1085#1091
            #1040#1075#1088#1077#1075#1072#1094#1080#1103' '#1087#1086' '#1089#1090#1072#1085#1094#1080#1080)
        end
      end
    end
  end
end
