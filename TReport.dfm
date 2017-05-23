object Form2: TForm2
  Left = 137
  Top = 0
  BorderStyle = bsDialog
  Caption = #1054#1090#1095#1077#1090' '#1086' '#1087#1077#1088#1077#1074#1086#1079#1082#1077
  ClientHeight = 574
  ClientWidth = 1071
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnActivate = FormActivate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1071
    Height = 574
    Align = alClient
    Caption = #1054#1090#1095#1077#1090' '#1087#1086#1076#1075#1086#1090#1074#1072#1083#1080#1074#1072#1077#1090#1089#1103'...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 1071
    Height = 574
    Align = alClient
    Caption = 'Panel2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object StringGrid1: TStringGrid
      Left = 1
      Top = 1
      Width = 1069
      Height = 572
      Align = alClient
      ColCount = 3
      DefaultColWidth = 100
      DrawingStyle = gdsGradient
      FixedCols = 0
      RowCount = 2
      GradientEndColor = clMenu
      ScrollBars = ssVertical
      TabOrder = 0
      OnDrawCell = StringGrid1DrawCell
      ColWidths = (
        100
        100
        100)
      RowHeights = (
        24
        24)
    end
  end
end
