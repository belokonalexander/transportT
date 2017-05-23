object Form3: TForm3
  Left = 411
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
      Height = 435
      Align = alClient
      TabOrder = 0
      OnSetEditText = ValueListEditor1SetEditText
      ExplicitHeight = 447
      ColWidths = (
        228
        236)
      RowHeights = (
        18
        18)
    end
    object Panel2: TPanel
      Left = 1
      Top = 436
      Width = 470
      Height = 48
      Align = alBottom
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      object Button2: TSpeedButton
        AlignWithMargins = True
        Left = 305
        Top = 4
        Width = 161
        Height = 40
        Hint = '123'
        Align = alRight
        Caption = #1054#1090#1084#1077#1085#1072
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clHotLight
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = Button2Click
        ExplicitLeft = 1075
        ExplicitTop = 6
        ExplicitHeight = 33
      end
      object Button1: TSpeedButton
        AlignWithMargins = True
        Left = 138
        Top = 4
        Width = 161
        Height = 40
        Hint = '123'
        Align = alRight
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clHotLight
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = Button1Click
        ExplicitLeft = 1075
        ExplicitTop = 6
        ExplicitHeight = 33
      end
    end
  end
end
