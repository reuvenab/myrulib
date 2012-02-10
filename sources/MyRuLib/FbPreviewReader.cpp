#include "FbPreviewReader.h"
#include "FbViewThread.h"
#include "FbViewData.h"

//-----------------------------------------------------------------------------
//  FbPreviewReader::RootHandler
//-----------------------------------------------------------------------------

FB2_BEGIN_KEYHASH(FbPreviewReader::RootHandler)
	KEY( "description" , Descr  );
	KEY( "binary"      , Binary );
FB2_END_KEYHASH

FbParserXML::BaseHandler * FbPreviewReader::RootHandler::NewNode(const wxString &name, const FbStringHash &atts)
{
	switch (toKeyword(name)) {
		case Descr: 
			new DescrHandler(m_reader, name);
		case Binary: {
			wxString file = Value(atts, wxT("id"));
			if (m_reader.m_images.Index(file) != wxNOT_FOUND)
				return new ImageHandler(m_reader, name, file);
			} return NULL;
		default: 
			return NULL;
	}
}

//-----------------------------------------------------------------------------
//  FbPreviewReader::DescrHandler
//-----------------------------------------------------------------------------

FB2_BEGIN_KEYHASH(FbPreviewReader::DescrHandler)
	KEY( "title-info"   , Title   );
	KEY( "publish-info" , Publish );
FB2_END_KEYHASH

FbParserXML::BaseHandler * FbPreviewReader::DescrHandler::NewNode(const wxString &name, const FbStringHash &atts)
{
	switch (toKeyword(name)) {
		case Title : 
		case Publish : 
		default: return NULL;
	}
}

//-----------------------------------------------------------------------------
//  FbPreviewReader
//-----------------------------------------------------------------------------

FbParserXML::BaseHandler * FbPreviewReader::CreateHandler(const wxString &name)
{
	return name == wxT("fictionbook") ? new RootHandler(*this, name) : NULL;
}

/*
	switch (Section()) {
		case fbsDescr: {
			if (*this >= wxT("fictionbook/description/title-info/annotation")) {
				m_annt << wxString::Format(wxT("<%s>"), name.c_str());
			} else if (*this == wxT("fictionbook/description/title-info/coverpage")) {
				if (name == wxT("image")) AppendImg(atts);
			} else if (*this == wxT("fictionbook/description/publish-info")) {
				if (name == wxT("isbn")) m_isbn.Empty();
			}
		} break;
		case fbsBody: {
			if (m_parsebody) m_annt << wxString::Format(wxT("<%s>"), name.c_str());
		} break;
		case fbsBinary: {
		} break;
		case fbsNone: {
			if (name == wxT("binary")) StartImg(atts);
		} break;
	}
	return true;

bool FbPreviewReader::TxtNode(const wxString &text)
{
	switch (Section()) {
		case fbsDescr: {
			if (*this >= wxT("fictionbook/description/title-info/annotation")) {
				m_annt << text;
			} else if (*this == wxT("fictionbook/description/publish-info/isbn")) {
				m_isbn << text;
			}
		} break;
		case fbsBody: {
			if (m_parsebody) m_annt << text;
		} break;
		case fbsBinary: {
			if (m_saveimage) m_imagedata << text;
		} break;
		case fbsNone: {
		} break;
	}
	return true;
}

bool FbPreviewReader::EndNode(const wxString &name)
{
	switch (Section()) {
		case fbsDescr: {
			if (*this >= wxT("fictionbook/description/title-info/annotation")) {
				m_annt << wxString::Format(wxT("</%s>"), name.c_str());
			}
		} break;
		case fbsBody: {
			if (m_parsebody) {
				m_annt << wxString::Format(wxT("<%s>"), name.c_str());
				if (m_annt.Length() > 1000) {
					m_data.SetText(FbViewData::ANNT, m_annt);
					if (m_images.Count()==0) Stop();
					m_thread.SendHTML(m_data);
					m_parsebody = false;
				}
			}
		} break;
		case fbsBinary: {
		} break;
		case fbsNone: {
			if (name == wxT("description")) {
				m_parsebody = m_annt.IsEmpty();
				if (!m_parsebody) {
					m_data.SetText(FbViewData::ANNT, m_annt);
					if (m_images.Count() == 0) Stop();
				}
				m_data.SetText(FbViewData::ISBN, m_isbn);
				m_thread.SendHTML(m_data);
			} else if (name == wxT("binary")) {
				if (m_saveimage) {
					m_data.AddImage(m_imagename, m_imagedata);
					m_thread.SendHTML(m_data);
				}
			}
		} break;
	}
	return true;
}

*/

void FbPreviewReader::AppendImg(const FbStringHash &atts)
{
	FbStringHash::const_iterator it;
	for( it = atts.begin(); it != atts.end(); ++it ) {
		wxString name = it->first;
		if (name.Right(4) == wxT("href")) {
			wxString value = it->second;
			if (value.Left(1) == wxT("#")) value = value.Mid(1);
			m_images.Add(value);
			break;
		}
	}
}

void FbPreviewReader::StartImg(const FbStringHash &atts)
{
	FbStringHash::const_iterator it;
	for( it = atts.begin(); it != atts.end(); ++it ) {
		wxString name = it->first;
		if (name == wxT("id")) {
			wxString value = it->second;
			if (value.Left(1) == wxT("#")) value = value.Mid(1);
			m_saveimage = (m_images.Index(value) != wxNOT_FOUND);
			if (m_saveimage) {
				m_imagename = value;
				m_imagedata.Empty();
			}
			break;
		}
	}
}

