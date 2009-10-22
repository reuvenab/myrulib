#ifndef __FBCONST_H__
#define __FBCONST_H__

#include <wx/wx.h>

enum {
    ID_MASTER_LIST = wxID_HIGHEST + 1,
    ID_BOOKS_LISTCTRL,
    ID_BOOKS_INFO_PANEL,
    ID_PROGRESSBAR,
    ID_FIND_AUTHOR,
    ID_FIND_TITLE,
    ID_PROGRESS_START,
    ID_PROGRESS_UPDATE,
    ID_PROGRESS_FINISH,
    ID_MODE_TREE,
    ID_MODE_LIST,
    ID_SPLIT_HORIZONTAL,
    ID_SPLIT_VERTICAL,
    ID_FILTER_FB2,
    ID_FILTER_LIB,
    ID_FILTER_USR,
    ID_FOLDER,
    ID_ERROR,
    ID_LOG_TEXTCTRL,
    ID_BOOKINFO_UPDATE,
    ID_SEARCH_BOOK,
    ID_OPEN_WEB,
    ID_FRAME_AUTHOR,
    ID_FRAME_GENRES,
    ID_FRAME_FAVOUR,
    ID_FRAME_SEARCH,
    ID_FRAME_INFO,
    ID_FRAME_HTML,
    ID_FRAME_SEQ,
    ID_FRAME_DATE,
    ID_FRAME_ARCH,
    ID_UNSELECTALL,
    ID_OPEN_BOOK,
    ID_MENU_SEARCH,
    ID_MENU_AUTHOR,
    ID_MENU_DB_INFO,
    ID_MENU_VACUUM,
    ID_MENU_CONFIG,
    ID_EMPTY_BOOKS,
    ID_APPEND_BOOK,
    ID_APPEND_AUTHOR,
    ID_APPEND_SEQUENCE,
	ID_FOUND_NOTHING,
    ID_EDIT_COMMENTS,
	ID_APPEND_FOLDER,
	ID_MODIFY_FOLDER,
	ID_DELETE_FOLDER,
	ID_UPDATE_FOLDER,
	ID_HTML_DOCUMENT,
	ID_HTML_CAPTION,
	ID_HTML_COMMENT,
	ID_HTML_SUBMIT,
	ID_HTML_MODIFY,
	ID_OPEN_AUTHOR,
	ID_DOWNLOAD_BOOK,
	ID_DELETE_DOWNLOAD,
    ID_DATABASE_INFO,
    ID_FAVORITES_DEL,
    ID_RATING_0,
    ID_RATING_1,
    ID_RATING_2,
    ID_RATING_3,
    ID_RATING_4,
    ID_RATING_5,
    ID_LETTER_RU = wxID_HIGHEST + 100,
    ID_LETTER_EN = wxID_HIGHEST + 150,
    ID_FAVORITES_ADD = wxID_HIGHEST + 200,
};

extern const wxString strProgramName;
extern const wxString strVersionInfo;
extern const wxString strHomePage;

extern const wxString alphabetRu;
extern const wxString alphabetEn;
extern const wxString strAlphabet;
extern const wxString strNobody;
extern const wxString strRusJE;
extern const wxString strRusJO;
extern const wxString strOtherSequence;
extern const wxString strBookNotFound;

extern const int ciNoAuthor;
extern const int ciMaxImageWidth;

extern const wxString strRating [];

#endif // __FBCONST_H__
