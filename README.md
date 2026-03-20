# GCMonitor

UObect生成・破棄により起きる出来事を観測するためのプログラムです。<br>
主にガベージコレクションの挙動を追うために作りました。<br>
現在はUObject、AActorをサポートしています。<br>

<img src="./Image/Top.png" width="640" height="360"/>

## 動作環境
- Unreal Engine 5.6.1
- VisualStudio 2022

### 外部ライブラリ

- [Unreal ImGuiプラグイン (benui-dev/UnrealImGui)：MIT License](https://github.com/benui-dev/UnrealImGui)  
  Unreal Engine 5 向けに Dear ImGui を統合するプラグイン。ImPlotなどの拡張にも対応。

- [Dear ImGui (Omar Cornut)：MIT License](https://github.com/ocornut/imgui)  
  軽量で移植性の高いGUIライブラリ。Unreal ImGuiはこのライブラリをUnreal Engineに対応させたもの。

## 構成

<img src="./Image/Map.png"/>

### 主要クラス

- [AImGuiVisualizer](https://github.com/7jibi8rm/GCMonitor/blob/master/Source/GCMonitor/Public/ImGuiVisualizer.h)<br>
ImGuiを用いたメニューの実装です。<br>
画面上に表示されているUIは全てこのクラスが管理しています。<br>

- [AHolderActor](https://github.com/7jibi8rm/GCMonitor/blob/master/Source/GCMonitor/Public/HolderActor.h)<br>
観測対象となるUObject・AActorを管理するアクターです。<br>
AImGuiVisualizerからの要求に答えて実際の検証操作を実行します。<br>

- [AActorSubject](https://github.com/7jibi8rm/GCMonitor/blob/master/Source/GCMonitor/Public/ActorSubject.h)<br>
観測対象のAActorクラス<br>
ログ等の観測用処理が必要なため、AActorはそのまま使わず独自継承したクラスを使用。<br>

- [USubject](https://github.com/7jibi8rm/GCMonitor/blob/master/Source/GCMonitor/Public/Subject.h)<br>
観測対象のUObjectクラス<br>
AActorSubjectと同様に、観測用の処理のため独自継承しています。<br>

- [UTrackingSubsystem](https://github.com/7jibi8rm/GCMonitor/blob/master/Source/GCMonitor/Public/TrackingSubsystem.h)<br>
ログを管理しています。<br>
観測データを参照しやすいよう、ログ用文字列を独自クラスで管理しています。<br>