object Form3: TForm3
  Left = 823
  Top = 77
  BorderStyle = bsSingle
  Caption = 'Form3'
  ClientHeight = 485
  ClientWidth = 472
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
    Width = 472
    Height = 485
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object ValueListEditor1: TValueListEditor
      Left = 1
      Top = 1
      Width = 470
      Height = 447
      Align = alClient
      TabOrder = 0
      OnSetEditText = ValueListEditor1SetEditText
      ColWidths = (
        228
        236)
      RowHeights = (
        18
        18)
    end
    object Panel2: TPanel
      Left = 1
      Top = 448
      Width = 470
      Height = 36
      Align = alBottom
      TabOrder = 1
      object Button1: TButton
        AlignWithMargins = True
        Left = 310
        Top = 4
        Width = 75
        Height = 28
        Align = alRight
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        AlignWithMargins = True
        Left = 391
        Top = 4
        Width = 75
        Height = 28
        Align = alRight
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 1
        OnClick = Button2Click
      end
    end
  end
end
