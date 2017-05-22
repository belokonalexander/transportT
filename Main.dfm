object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'TransportT'
  ClientHeight = 667
  ClientWidth = 1324
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
    Width = 1324
    Height = 667
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 42
      Width = 226
      Height = 624
      Align = alLeft
      TabOrder = 0
      object Label1: TLabel
        Left = 21
        Top = 6
        Width = 87
        Height = 13
        Caption = #1053#1072#1095#1072#1083#1100#1085#1072#1103' '#1076#1072#1090#1072':'
      end
      object Label2: TLabel
        Left = 21
        Top = 52
        Width = 81
        Height = 13
        Caption = #1050#1086#1085#1077#1095#1085#1072#1103' '#1076#1072#1090#1072':'
      end
      object Button1: TButton
        Left = 32
        Top = 112
        Width = 153
        Height = 34
        Caption = #1047#1072#1087#1088#1086#1089' '#1076#1072#1085#1085#1099#1093
        TabOrder = 0
        OnClick = Button1Click
      end
      object Edit1: TEdit
        Left = 32
        Top = 25
        Width = 33
        Height = 21
        Hint = 'dd'
        Alignment = taCenter
        TabOrder = 1
      end
      object Edit2: TEdit
        Left = 80
        Top = 25
        Width = 33
        Height = 21
        Hint = 'mm'
        Alignment = taCenter
        TabOrder = 2
      end
      object Edit3: TEdit
        Left = 125
        Top = 25
        Width = 60
        Height = 21
        Hint = 'yyyy'
        Alignment = taCenter
        TabOrder = 3
        Text = '2013'
      end
      object Edit4: TEdit
        Left = 32
        Top = 71
        Width = 33
        Height = 21
        Hint = 'dd'
        Alignment = taCenter
        TabOrder = 4
      end
      object Edit5: TEdit
        Left = 80
        Top = 71
        Width = 33
        Height = 21
        Hint = 'mm'
        Alignment = taCenter
        TabOrder = 5
      end
      object Edit6: TEdit
        Left = 125
        Top = 71
        Width = 60
        Height = 21
        Hint = 'yyyy'
        Alignment = taCenter
        TabOrder = 6
        Text = '2013'
      end
      object Memo1: TMemo
        Left = 1
        Top = 518
        Width = 224
        Height = 105
        Align = alBottom
        Lines.Strings = (
          'Memo1')
        TabOrder = 7
        Visible = False
      end
      object ExecuteButton: TButton
        Left = 32
        Top = 152
        Width = 153
        Height = 34
        Caption = #1054#1087#1090#1080#1084#1080#1079#1080#1088#1086#1074#1072#1090#1100
        Enabled = False
        TabOrder = 8
        OnClick = ExecuteButtonClick
      end
    end
    object Panel3: TPanel
      Left = 227
      Top = 42
      Width = 1096
      Height = 624
      Align = alClient
      TabOrder = 1
      object Edit8: TEdit
        Left = 1
        Top = 1
        Width = 1094
        Height = 21
        Align = alTop
        TabOrder = 0
      end
      object Panel5: TPanel
        Left = 1
        Top = 22
        Width = 1094
        Height = 27
        Align = alTop
        TabOrder = 1
        object Panel6: TPanel
          Left = 820
          Top = 1
          Width = 273
          Height = 25
          Align = alClient
          Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
          TabOrder = 0
        end
        object Panel7: TPanel
          Left = 1
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1055#1086#1089#1090#1072#1074#1097#1080#1082#1080
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentBackground = False
          ParentFont = False
          TabOrder = 1
        end
        object Panel8: TPanel
          Left = 274
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1055#1086#1090#1088#1077#1073#1080#1090#1077#1083#1080
          TabOrder = 2
        end
        object Panel9: TPanel
          Left = 547
          Top = 1
          Width = 273
          Height = 25
          Align = alLeft
          Caption = #1052#1072#1090#1088#1080#1094#1072' '#1090#1072#1088#1080#1092#1086#1074
          TabOrder = 3
        end
      end
      object Panel10: TPanel
        Left = 1
        Top = 49
        Width = 1094
        Height = 574
        Align = alClient
        Caption = 'Panel10'
        TabOrder = 2
        object ProvidersGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1092
          Height = 531
          Align = alClient
          ColCount = 6
          Ctl3D = True
          DefaultColWidth = 180
          FixedCols = 0
          RowCount = 2
          ParentCtl3D = False
          ScrollBars = ssHorizontal
          TabOrder = 0
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
          Top = 532
          Width = 1092
          Height = 41
          Align = alBottom
          TabOrder = 1
          object Label3: TLabel
            Left = 16
            Top = 5
            Width = 110
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1089#1090#1072#1074#1097#1080#1082#1086#1074':'
          end
          object Label4: TLabel
            Left = 85
            Top = 22
            Width = 41
            Height = 13
            Caption = #1047#1072#1087#1072#1089#1099':'
          end
          object ProvidersCount: TLabel
            Left = 132
            Top = 5
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
            Top = 22
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
        Width = 1094
        Height = 574
        Align = alClient
        Caption = 'Panel11'
        TabOrder = 3
        object Panel15: TPanel
          Left = 1
          Top = 532
          Width = 1092
          Height = 41
          Align = alBottom
          TabOrder = 0
          object Label5: TLabel
            Left = 16
            Top = 5
            Width = 114
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1090#1088#1077#1073#1080#1090#1077#1083#1077#1081':'
          end
          object Label6: TLabel
            Left = 60
            Top = 22
            Width = 70
            Height = 13
            Caption = #1055#1086#1090#1088#1077#1073#1085#1086#1089#1090#1080':'
          end
          object RecieversCount: TLabel
            Left = 132
            Top = 5
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
            Top = 22
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
          object Button2: TButton
            AlignWithMargins = True
            Left = 941
            Top = 4
            Width = 147
            Height = 33
            Align = alRight
            Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100
            TabOrder = 0
            OnClick = Button2Click
          end
        end
        object RecieversGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1092
          Height = 531
          Align = alClient
          ColCount = 6
          DefaultColWidth = 180
          FixedCols = 0
          RowCount = 2
          ScrollBars = ssHorizontal
          TabOrder = 1
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
        Width = 1094
        Height = 574
        Align = alClient
        Caption = 'Panel12'
        TabOrder = 4
        object TarifsGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1092
          Height = 572
          Align = alClient
          ColCount = 6
          DefaultColWidth = 180
          FixedCols = 0
          RowCount = 2
          ParentColor = True
          ScrollBars = ssHorizontal
          TabOrder = 0
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
        Width = 1094
        Height = 574
        Align = alClient
        Caption = 'Panel13'
        TabOrder = 5
        object ResultsGrid: TStringGrid
          Left = 1
          Top = 1
          Width = 1092
          Height = 531
          Align = alClient
          ColCount = 6
          DefaultColWidth = 180
          FixedCols = 0
          RowCount = 2
          ParentColor = True
          ScrollBars = ssVertical
          TabOrder = 0
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
          Top = 532
          Width = 1092
          Height = 41
          Align = alBottom
          TabOrder = 1
          object Label7: TLabel
            Left = 16
            Top = 15
            Width = 48
            Height = 13
            Caption = #1047#1072#1090#1088#1072#1090#1099':'
          end
          object ResultCost: TLabel
            Left = 70
            Top = 15
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
      Width = 1322
      Height = 41
      Align = alTop
      TabOrder = 2
    end
  end
  object TransportdbConnection: TFDConnection
    Params.Strings = (
      'ConnectionDef=TransportDB')
    Connected = True
    LoginPrompt = False
    Left = 58
    Top = 286
  end
end
