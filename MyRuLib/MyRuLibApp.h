#ifndef __MYRULIBAPP_H__
#define __MYRULIBAPP_H__

#include <wx/wx.h>
#include <wx/thread.h>
#include <wx/filename.h>
#include "FbDatabase.h"

#ifdef __WXDEBUG__
#include <wx/memory.h>
#endif // __WXDEBUG__

class FbLocale;

class FbCollection;

class MyRuLibApp : public wxApp
{
	public:
		MyRuLibApp();
		virtual ~MyRuLibApp();
		virtual bool OnInit();
		virtual int OnExit();
		bool OpenDatabase(const wxString &filename);
		const wxString GetAppData();
		const wxString GetAppPath();
		void Localize();
		FbCollection * GetCollection() { return m_collection; }
	protected:
		virtual void OnUnhandledException() {}
		virtual bool OnExceptionInMainLoop() { return true; }
	private:
		void OpenLog();
		wxFileName GetDatabaseFilename(FbDatabase &database);
		void SetAppData(const wxString &filename);
		void LoadBlankImage();
	private:
		wxCriticalSection m_section;
		wxString m_datafile;
		FbLocale * m_locale;
		FbCollection * m_collection;
};

DECLARE_APP(MyRuLibApp)

#endif // __MYRULIBAPP_H__
