object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'TransportT'
  ClientHeight = 667
  ClientWidth = 1312
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1312
    Height = 667
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 1324
    object Panel2: TPanel
      Left = 1
      Top = 36
      Width = 220
      Height = 525
      Align = alLeft
      TabOrder = 0
      ExplicitLeft = -3
      ExplicitTop = 48
      ExplicitHeight = 519
      object Label1: TLabel
        Left = 18
        Top = 131
        Width = 87
        Height = 13
        Caption = #1053#1072#1095#1072#1083#1100#1085#1072#1103' '#1076#1072#1090#1072':'
      end
      object Label2: TLabel
        Left = 18
        Top = 190
        Width = 81
        Height = 13
        Caption = #1050#1086#1085#1077#1095#1085#1072#1103' '#1076#1072#1090#1072':'
      end
      object Label9: TLabel
        Left = 18
        Top = 6
        Width = 71
        Height = 13
        Caption = #1042#1099#1073#1086#1088' '#1086#1090#1095#1077#1090#1072
      end
      object Label8: TLabel
        Left = 147
        Top = 159
        Width = 60
        Height = 13
        Caption = 'dd/mm/yyyy'
        Enabled = False
      end
      object Label10: TLabel
        Left = 147
        Top = 218
        Width = 60
        Height = 13
        Caption = 'dd/mm/yyyy'
        Enabled = False
      end
      object ExecuteButton: TSpeedButton
        Left = 24
        Top = 308
        Width = 161
        Height = 42
        Hint = '123'
        Caption = #1054#1087#1090#1080#1084#1080#1079#1080#1088#1086#1074#1072#1090#1100
        Enabled = False
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clHotLight
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = ExecuteButtonClick
      end
      object Button1: TSpeedButton
        Left = 24
        Top = 260
        Width = 161
        Height = 42
        Hint = '123'
        Caption = #1047#1072#1087#1088#1086#1089' '#1076#1072#1085#1085#1099#1093
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clHotLight
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = Button1Click
      end
      object SpeedButton1: TSpeedButton
        Left = 24
        Top = 52
        Width = 161
        Height = 42
        Hint = '123'
        Caption = #1054#1090#1082#1088#1099#1090#1100
        Enabled = False
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clHotLight
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = SpeedButton1Click
      end
      object Edit1: TEdit
        Left = 18
        Top = 156
        Width = 25
        Height = 21
        Hint = 'dd'
        Alignment = taCenter
        AutoSelect = False
        Ctl3D = True
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 0
      end
      object Edit2: TEdit
        Left = 57
        Top = 156
        Width = 25
        Height = 21
        Hint = 'mm'
        Alignment = taCenter
        NumbersOnly = True
        TabOrder = 1
      end
      object Edit3: TEdit
        Left = 95
        Top = 156
        Width = 40
        Height = 21
        Hint = 'yyyy'
        Alignment = taCenter
        NumbersOnly = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 2
        Text = '2013'
      end
      object Edit4: TEdit
        Left = 18
        Top = 215
        Width = 25
        Height = 21
        Hint = 'dd'
        Alignment = taCenter
        NumbersOnly = True
        TabOrder = 3
      end
      object Edit5: TEdit
        Left = 57
        Top = 215
        Width = 25
        Height = 21
        Hint = 'mm'
        Alignment = taCenter
        NumbersOnly = True
        TabOrder = 4
      end
      object ComboBox1: TComboBox
        Left = 18
        Top = 25
        Width = 175
        Height = 21
        Style = csDropDownList
        TabOrder = 5
        OnChange = ComboBox1Change
        OnDropDown = ComboBox1DropDown
      end
      object Panel17: TPanel
        Left = 0
        Top = 107
        Width = 220
        Height = 2
        Caption = 'Panel17'
        TabOrder = 6
      end
      object Edit6: TEdit
        Left = 95
        Top = 215
        Width = 40
        Height = 21
        Hint = 'yyyy'
        Alignment = taCenter
        NumbersOnly = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 7
        Text = '2013'
      end
    end
    object Panel3: TPanel
      Left = 221
      Top = 36
      Width = 1090
      Height = 525
      Align = alClient
      TabOrder = 1
      ExplicitLeft = 227
      ExplicitTop = 42
      ExplicitWidth = 1096
      ExplicitHeight = 624
      object Edit8: TEdit
        Left = 1
        Top = 1
        Width = 1088
        Height = 21
        Align = alTop
        Enabled = False
        TabOrder = 0
        ExplicitWidth = 1094
      end
      object Panel5: TPanel
        Left = 1
        Top = 22
        Width = 1088
        Height = 27
        Align = alTop
        TabOrder = 1
        ExplicitWidth = 1094
        object Panel6: TPanel
          Left = 820
          Top = 1
          Width = 267
          Height = 25
          Align = alClient
          Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
          Color = clMenu
          ParentBackground = False
          TabOrder = 0
          ExplicitWidth = 273
        end
        object Panel7: TPanel
          Left = 1
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1055#1086#1089#1090#1072#1074#1097#1080#1082#1080
          Color = clMenu
          DoubleBuffered = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentDoubleBuffered = False
          ParentFont = False
          ParentShowHint = False
          ShowHint = False
          TabOrder = 1
        end
        object Panel8: TPanel
          Left = 274
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1055#1086#1090#1088#1077#1073#1080#1090#1077#1083#1080
          Color = clMenu
          ParentBackground = False
          TabOrder = 2
          ExplicitLeft = 280
          ExplicitTop = -3
        end
        object Panel9: TPanel
          Left = 547
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1052#1072#1090#1088#1080#1094#1072' '#1090#1072#1088#1080#1092#1086#1074
          Color = clMenu
          ParentBackground = False
          TabOrder = 3
        end
      end
      object Panel10: TPanel
        Left = 1
        Top = 49
        Width = 1088
        Height = 475
        Align = alClient
        Caption = 'Panel10'
        TabOrder = 2
        ExplicitWidth = 1094
        ExplicitHeight = 574
        object ProvidersGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1086
          Height = 425
          Align = alClient
          ColCount = 6
          Ctl3D = True
          DefaultColWidth = 180
          DrawingStyle = gdsGradient
          FixedCols = 0
          RowCount = 2
          GradientEndColor = clMenu
          ParentCtl3D = False
          ScrollBars = ssVertical
          TabOrder = 0
          ExplicitHeight = 419
          ColWidths = (
            180
            180
            180
            180
            180
            180)
          RowHeights = (
            24
            24)
        end
        object Panel14: TPanel
          Left = 1
          Top = 426
          Width = 1086
          Height = 48
          Align = alBottom
          TabOrder = 1
          ExplicitTop = 424
          ExplicitWidth = 1098
          object Label3: TLabel
            Left = 16
            Top = 8
            Width = 110
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1089#1090#1072#1074#1097#1080#1082#1086#1074':'
          end
          object Label4: TLabel
            Left = 85
            Top = 25
            Width = 41
            Height = 13
            Caption = #1047#1072#1087#1072#1089#1099':'
          end
          object ProvidersCount: TLabel
            Left = 132
            Top = 8
            Width = 7
            Height = 13
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object ReserveCount: TLabel
            Left = 132
            Top = 25
            Width = 7
            Height = 13
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
        end
      end
      object Panel11: TPanel
        Left = 1
        Top = 49
        Width = 1088
        Height = 475
        Align = alClient
        Caption = 'Panel11'
        TabOrder = 3
        ExplicitWidth = 1094
        ExplicitHeight = 574
        object Panel15: TPanel
          Left = 1
          Top = 426
          Width = 1086
          Height = 48
          Align = alBottom
          TabOrder = 0
          ExplicitTop = 420
          ExplicitWidth = 1098
          object Label5: TLabel
            Left = 16
            Top = 8
            Width = 114
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1090#1088#1077#1073#1080#1090#1077#1083#1077#1081':'
          end
          object Label6: TLabel
            Left = 60
            Top = 25
            Width = 70
            Height = 13
            Caption = #1055#1086#1090#1088#1077#1073#1085#1086#1089#1090#1080':'
          end
          object RecieversCount: TLabel
            Left = 132
            Top = 8
            Width = 7
            Height = 13
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object NeedsCount: TLabel
            Left = 132
            Top = 25
            Width = 7
            Height = 13
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Button2: TSpeedButton
            AlignWithMargins = True
            Left = 921
            Top = 4
            Width = 161
            Height = 40
            Hint = '123'
            Align = alRight
            Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
            Flat = True
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clHotLight
            Font.Height = -16
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            OnClick = Button2Click
            ExplicitLeft = 32
            ExplicitTop = 6
            ExplicitHeight = 42
          end
        end
        object RecieversGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1086
          Height = 425
          Align = alClient
          ColCount = 6
          DefaultColWidth = 180
          DrawingStyle = gdsGradient
          FixedCols = 0
          RowCount = 2
          GradientEndColor = clMenu
          ScrollBars = ssVertical
          TabOrder = 1
          ExplicitHeight = 419
          ColWidths = (
            180
            180
            180
            180
            180
            180)
          RowHeights = (
            24
            24)
        end
      end
      object Panel12: TPanel
        Left = 1
        Top = 49
        Width = 1088
        Height = 475
        Align = alClient
        Caption = 'Panel12'
        TabOrder = 4
        ExplicitWidth = 1094
        ExplicitHeight = 574
        object TarifsGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1086
          Height = 473
          Align = alClient
          Color = clWhite
          ColCount = 6
          DefaultColWidth = 180
          DrawingStyle = gdsGradient
          FixedCols = 0
          RowCount = 2
          GradientEndColor = clMenu
          ScrollBars = ssVertical
          TabOrder = 0
          ExplicitHeight = 467
          ColWidths = (
            180
            180
            180
            180
            180
            180)
          RowHeights = (
            24
            24)
        end
      end
      object Panel13: TPanel
        Left = 1
        Top = 49
        Width = 1088
        Height = 475
        Align = alClient
        Caption = 'Panel13'
        TabOrder = 5
        ExplicitWidth = 1094
        ExplicitHeight = 574
        object ResultsGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1086
          Height = 425
          ParentCustomHint = False
          Align = alClient
          BiDiMode = bdLeftToRight
          Color = clWhite
          ColCount = 6
          Ctl3D = True
          DefaultColWidth = 180
          DoubleBuffered = False
          DrawingStyle = gdsGradient
          FixedColor = clSilver
          FixedCols = 0
          RowCount = 2
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GradientEndColor = clMenu
          ParentBiDiMode = False
          ParentCtl3D = False
          ParentDoubleBuffered = False
          ParentFont = False
          ParentShowHint = False
          ScrollBars = ssVertical
          ShowHint = False
          TabOrder = 0
          ExplicitLeft = 0
          ExplicitHeight = 419
          ColWidths = (
            180
            180
            180
            180
            180
            180)
          RowHeights = (
            24
            24)
        end
        object Panel16: TPanel
          Left = 1
          Top = 426
          Width = 1086
          Height = 48
          Align = alBottom
          TabOrder = 1
          ExplicitTop = 424
          ExplicitWidth = 1098
          object Label7: TLabel
            Left = 16
            Top = 18
            Width = 48
            Height = 13
            Caption = #1047#1072#1090#1088#1072#1090#1099':'
          end
          object ResultCost: TLabel
            Left = 70
            Top = 18
            Width = 7
            Height = 13
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
        end
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 1310
      Height = 35
      Align = alTop
      TabOrder = 2
      object SpeedButton2: TSpeedButton
        Left = 6
        Top = 5
        Width = 23
        Height = 22
      end
    end
    object Memo1: TMemo
      Left = 1
      Top = 561
      Width = 1310
      Height = 105
      Align = alBottom
      Lines.Strings = (
        'Memo1')
      TabOrder = 3
      Visible = False
      ExplicitTop = 518
      ExplicitWidth = 224
    end
  end
  object TransportdbConnection: TFDConnection
    Params.Strings = (
      'ConnectionDef=TransportDB')
    Connected = True
    LoginPrompt = False
    Left = 130
    Top = 502
  end
end
