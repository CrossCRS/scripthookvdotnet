#pragma once

#include "Viewport.hpp"
#include "UIRectangle.hpp"
#include "UIText.hpp"
#include "MenuItem.hpp"

namespace GTA
{
	interface class MenuItem;
	ref class Viewport;

	public ref class MenuBase
	{
	public:
		/** Draws the menu */
		virtual void Draw() { }

		//Drawing with an offset implies that this menu is not the active one
		/** Draws the menu with an offset */
		virtual void Draw(System::Drawing::Size offset) { }

		/** Called when the menu is first added to the Viewport */
		virtual void Initialize() { }

		/** Called when the menu gains or regains focus */
		virtual void OnOpen() { }

		/** Called when the user hits the back button or unfocuses from this menu */
		virtual void OnClose() { }

		/** Called when the user hits the activate button */
		virtual void OnActivate() { }

		/** Called when the user changes what element is selected (i.e. up and down) */
		virtual void OnChangeSelection(bool down) { }

		/** Called when the user changes the current element (i.e. left and right) */
		virtual void OnChangeItem(bool right) { }

	public:
		property Viewport ^Parent;
		property System::Drawing::Color HeaderColor;
		property System::Drawing::Color HeaderTextColor;
		property int HeaderFont;
		property float HeaderTextScale;
		property bool HeaderCentered;
		property System::Drawing::Color FooterColor;		
		property System::Drawing::Color FooterTextColor;
		property int FooterFont;
		property float FooterTextScale;
		property bool FooterCentered;
		property System::Drawing::Color SelectedItemColor;
		property System::Drawing::Color UnselectedItemColor;
		property System::Drawing::Color SelectedTextColor;
		property System::Drawing::Color UnselectedTextColor;
		property int ItemFont;
		property float ItemTextScale;
		property bool ItemTextCentered;
		property System::Drawing::Point Position;
		property System::String ^Caption;
	};

	public ref class Menu : MenuBase
	{
	public:
		Menu(System::String ^headerCaption, array<MenuItem ^> ^items);

	public:
		virtual void Draw() override;
		virtual void Draw(System::Drawing::Size offset) override;
		virtual void Initialize() override;
		virtual void OnOpen() override;
		virtual void OnClose() override;
		virtual void OnActivate() override;
		virtual void OnChangeSelection(bool down) override;
		virtual void OnChangeItem(bool right) override;

	public:
		property int Width;
		property int HeaderHeight;
		property int FooterHeight;
		property int ItemHeight;
		property bool HasFooter;

	private:
		UIRectangle ^mHeaderRect = nullptr, ^mFooterRect = nullptr;
		UIText ^mHeaderText = nullptr, ^mFooterText = nullptr;

		System::Collections::Generic::List<MenuItem ^> ^mItems = gcnew System::Collections::Generic::List<MenuItem ^>();
		int mSelectedIndex = -1;
		System::String ^mFooterDescription = "footer description";
	};
	
	public ref class MessageBox : MenuBase {
	public:
		MessageBox(System::String ^headerCaption, System::Action ^yesAction, System::Action ^noAction);

	public:
		virtual void Draw() override;
		virtual void Draw(System::Drawing::Size offset) override;
		virtual void Initialize() override;
		virtual void OnOpen() override;
		virtual void OnClose() override;
		virtual void OnActivate() override;
		virtual void OnChangeSelection(bool down) override;
		virtual void OnChangeItem(bool right) override;

	public:
		property int Width;
		property int Height;
		property int ButtonHeight;

		/** Use Ok and Cancel instead of Yes and No */
		property bool OkCancel;

	private:
		UIRectangle ^mBodyRect = nullptr, ^mYesRect = nullptr, ^mNoRect = nullptr;
		UIText ^mText, ^mYesText, ^mNoText;
		System::Action ^mYesAction = nullptr, ^mNoAction = nullptr;
		bool mSelection = true;
	};
}