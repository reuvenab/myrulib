#ifndef __FBPARAMSDLG_H__
#define __FBPARAMSDLG_H__

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/arrimpl.cpp>
#include <wx/fontpicker.h>
#include <wx/spinctrl.h>
#include <wx/wxsqlite3.h>
#include "FbWindow.h"
#include "FbTreeModel.h"

class FbTreeViewCtrl;

///////////////////////////////////////////////////////////////////////////////
/// Class FbParamsDlg
///////////////////////////////////////////////////////////////////////////////
class FbParamsDlg : private FbDialog
{
	private:
		enum ID {
			ID_AUTO_DOWNLD = 1000,
			ID_TEMP_DEL,
			ID_TEMP_DIR_TXT,
			ID_TEMP_DIR_BTN,
			ID_WINE_DIR,
			ID_DOWNLOAD_DIR_TXT,
			ID_DOWNLOAD_DIR_BTN,
			ID_USE_PROXY,
			ID_PROXY_ADDR,
			ID_HTTP_IMAGES,
			ID_LIBRUSEC_URL,
			ID_EXTERNAL_TXT,
			ID_EXTERNAL_BTN,
			ID_DEL_DOWNLOAD,
			ID_TRANSLIT_FOLDER,
			ID_TRANSLIT_FILE,
			ID_FOLDER_FORMAT,
			ID_FILE_FORMAT,
			ID_USE_SYMLINKS,
			ID_TYPE_LIST,
			ID_TYPE_TOOLBAR,
			ID_APPEND_TYPE,
			ID_MODIFY_TYPE,
			ID_DELETE_TYPE,
			ID_SCRIPT_LIST,
			ID_SCRIPT_TOOLBAR,
			ID_APPEND_SCRIPT,
			ID_MODIFY_SCRIPT,
			ID_DELETE_SCRIPT,
			ID_FONT_CLEAR,
			ID_FONT_MAIN,
			ID_FONT_HTML,
			ID_FONT_TOOL,
			ID_FONT_DLG,
			ID_REMOVE_FILES,
			ID_AUTOHIDE_COLUMN,
			ID_LIMIT_CHECK,
			ID_LIMIT_COUNT,
			ID_SAVE_FULLPATH,
			ID_LETTERS,
		};
		class LoadThread: public wxThread
		{
			public:
				LoadThread(wxEvtHandler * frame)
					:wxThread(wxTHREAD_JOINABLE), m_frame(frame) {}
			protected:
				virtual void * Entry();
			private:
				void LoadTypes(wxSQLite3Database &database);
				void LoadScripts(wxSQLite3Database &database);
				wxEvtHandler * m_frame;
		};
		class PanelFont: public wxPanel
		{
			public:
				PanelFont(wxWindow *parent);
			private:
				void AppendItem(wxFlexGridSizer* fgSizer, const wxString& name, wxWindowID winid = wxID_ANY);
		};
		class PanelInternet: public wxPanel
		{
			public:
				PanelInternet(wxWindow *parent);
		};
		class PanelExport: public wxPanel
		{
			public:
				PanelExport(wxWindow *parent);
		};
		class PanelTypes: public wxPanel
		{
			public:
				PanelTypes(wxWindow *parent);
		};
		class PanelInterface: public wxPanel
		{
			public:
				PanelInterface(wxWindow *parent);
		};
		class TypeData: public FbModelData
		{
			public:
				TypeData(wxSQLite3ResultSet &result);
				TypeData(const wxString &type, const wxString &command = wxEmptyString)
					: m_type(type), m_command(command), m_modified(true) {}
			public:
				virtual wxString GetValue(FbModel & model, size_t col = 0) const;
				bool IsModified() { return m_modified; }
			protected:
				wxString m_type;
				wxString m_command;
				bool m_modified;
				DECLARE_CLASS(ScriptData);
		};
		class ScriptData: public FbModelData
		{
			public:
				ScriptData(wxSQLite3ResultSet &result);
				ScriptData(int code, const wxString &name, const wxString &text)
					: m_code(code), m_name(name), m_text(text), m_modified(true) {}
			public:
				virtual wxString GetValue(FbModel & model, size_t col = 0) const;
				int GetCode() { return m_code; }
				bool IsModified() { return m_modified; }
			protected:
				int m_code;
				wxString m_name;
				wxString m_text;
				bool m_modified;
				DECLARE_CLASS(ScriptData);
		};
		class ScriptDlg: public FbDialog
		{
			public:
				ScriptDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE  | wxRESIZE_BORDER);
				static bool Execute(wxWindow* parent, const wxString& title, wxString &name, wxString &text);
			protected:
				void OnLetterClicked(wxCommandEvent& event);
				wxTextCtrl m_name;
				wxTextCtrl m_text;
				wxString m_letters;
		};
	public:
		FbParamsDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE  | wxRESIZE_BORDER);
		virtual ~FbParamsDlg();
		static void Execute(wxWindow* parent);
	private:
		void Assign(bool write);
		void SetFont( wxWindowID id, wxFont font );
		void SelectApplication();
		void SaveData();
		void DeleteTypes(wxSQLite3Database &database);
		void DeleteScripts(wxSQLite3Database &database);
		void SaveTypes(wxSQLite3Database &database);
		void SaveScripts(wxSQLite3Database &database);
		void SaveScripts();
		void EnableTool(wxWindowID id, bool enable);
		void FillFormats(FbTreeViewCtrl * treeview, FbModel * model);
	private:
        void OnClose( wxCloseEvent& event );
		void OnSelectFolderClick( wxCommandEvent& event );
		void OnAppendType( wxCommandEvent& event );
		void OnModifyType( wxCommandEvent& event );
		void OnDeleteType( wxCommandEvent& event );
		void OnAppendScript( wxCommandEvent& event );
		void OnModifyScript( wxCommandEvent& event );
		void OnDeleteScript( wxCommandEvent& event );
		void OnTypeActivated( wxTreeEvent & event );
		void OnScriptActivated( wxTreeEvent & event );
		void OnFontClear( wxCommandEvent& event );
		void OnModel( FbModelEvent& event );
	private:
		wxArrayString m_del_type;
		wxArrayInt m_del_scr;
		LoadThread m_thread;
		DECLARE_EVENT_TABLE()
};

#endif // __FBPARAMSDLG_H__