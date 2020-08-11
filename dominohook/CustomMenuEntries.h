#pragma once

#include <Windows.h>
#include "CPortalView.h"
#include "CMainFrame.h"
#include "Common.h"
#include "Settings.h"
#include "ReferenceAudio.h"

#define CUSTOM_RES_START 0xF007

#define CPORTALVIEW_MSGMAP_PTR_PTR 0x5601EC
#define CPORTALVIEW_MSGMAP_LEN 250
#define CMAINFRAME_MSGMAP_PTR_PTR 0x55D0F4
#define CMAINFRAME_MSGMAP_LEN 50

#define ID_CUSTOMITEM1 CUSTOM_RES_START

#define ID_REFAUDIO    CUSTOM_RES_START + 1
#define ID_SETTINGS    CUSTOM_RES_START + 2
#define ID_SEPARATOR   CUSTOM_RES_START + 3
#define ID_GITHUB      CUSTOM_RES_START + 4
#define ID_BUILDDATE   CUSTOM_RES_START + 5

enum AfxSig {
	AfxSig_end = 0,     // [marks end of message map]
	AfxSig_bD,      // BOOL (CDC*)
	AfxSig_bb,      // BOOL (BOOL)
	AfxSig_bWww,    // BOOL (CWnd*, UINT, UINT)
	AfxSig_hDWw,    // HBRUSH (CDC*, CWnd*, UINT)
	AfxSig_hDw,     // HBRUSH (CDC*, UINT)
	AfxSig_iwWw,    // int (UINT, CWnd*, UINT)
	AfxSig_iww,     // int (UINT, UINT)
	AfxSig_iWww,    // int (CWnd*, UINT, UINT)
	AfxSig_is,      // int (LPTSTR)
	AfxSig_lwl,     // LRESULT (WPARAM, LPARAM)
	AfxSig_lwwM,    // LRESULT (UINT, UINT, CMenu*)
	AfxSig_vv,      // void (void)
	AfxSig_vw,      // void (UINT)
	AfxSig_vww,     // void (UINT, UINT)
	AfxSig_vvii,    // void (int, int) // wParam is ignored
	AfxSig_vwww,    // void (UINT, UINT, UINT)
	AfxSig_vwii,    // void (UINT, int, int)
	AfxSig_vwl,     // void (UINT, LPARAM)
	AfxSig_vbWW,    // void (BOOL, CWnd*, CWnd*)
	AfxSig_vD,      // void (CDC*)
	AfxSig_vM,      // void (CMenu*)
	AfxSig_vMwb,    // void (CMenu*, UINT, BOOL)
	AfxSig_vW,      // void (CWnd*)
	AfxSig_vWww,    // void (CWnd*, UINT, UINT)
	AfxSig_vWp,     // void (CWnd*, CPoint)
	AfxSig_vWh,     // void (CWnd*, HANDLE)
	AfxSig_vwW,     // void (UINT, CWnd*)
	AfxSig_vwWb,    // void (UINT, CWnd*, BOOL)
	AfxSig_vwwW,    // void (UINT, UINT, CWnd*)
	AfxSig_vwwx,    // void (UINT, UINT)
	AfxSig_vs,      // void (LPTSTR)
	AfxSig_vOWNER,  // void (int, LPTSTR), force return TRUE
	AfxSig_iis,     // int (int, LPTSTR)
	AfxSig_wp,      // UINT (CPoint)
	AfxSig_wv,      // UINT (void)
	AfxSig_vPOS,    // void (WINDOWPOS*)
	AfxSig_vCALC,   // void (BOOL, NCCALCSIZE_PARAMS*)
	AfxSig_vNMHDRpl,    // void (NMHDR*, LRESULT*)
	AfxSig_bNMHDRpl,    // BOOL (NMHDR*, LRESULT*)
	AfxSig_vwNMHDRpl,   // void (UINT, NMHDR*, LRESULT*)
	AfxSig_bwNMHDRpl,   // BOOL (UINT, NMHDR*, LRESULT*)
	AfxSig_bHELPINFO,   // BOOL (HELPINFO*)
	AfxSig_vwSIZING,    // void (UINT, LPRECT) -- return TRUE
	AfxSig_cmdui,   // void (CCmdUI*)
	AfxSig_cmduiw,  // void (CCmdUI*, UINT)
	AfxSig_vpv,     // void (void*)
	AfxSig_bpv,     // BOOL (void*)
	AfxSig_vwwh,                // void (UINT, UINT, HANDLE)
	AfxSig_vwp,                 // void (UINT, CPoint)
	AfxSig_bw = AfxSig_bb,      // BOOL (UINT)
	AfxSig_bh = AfxSig_bb,      // BOOL (HANDLE)
	AfxSig_iw = AfxSig_bb,      // int (UINT)
	AfxSig_ww = AfxSig_bb,      // UINT (UINT)
	AfxSig_bv = AfxSig_wv,      // BOOL (void)
	AfxSig_hv = AfxSig_wv,      // HANDLE (void)
	AfxSig_vb = AfxSig_vw,      // void (BOOL)
	AfxSig_vbh = AfxSig_vww,    // void (BOOL, HANDLE)
	AfxSig_vbw = AfxSig_vww,    // void (BOOL, UINT)
	AfxSig_vhh = AfxSig_vww,    // void (HANDLE, HANDLE)
	AfxSig_vh = AfxSig_vw,      // void (HANDLE)
	AfxSig_viSS = AfxSig_vwl,   // void (int, STYLESTRUCT*)
	AfxSig_bwl = AfxSig_lwl,
	AfxSig_vwMOVING = AfxSig_vwSIZING,  // void (UINT, LPRECT) -- return TRUE
	AfxSig_vW2,                 // void (CWnd*) (CWnd* comes from lParam)
	AfxSig_bWCDS,               // BOOL (CWnd*, COPYDATASTRUCT*)
	AfxSig_bwsp,                // BOOL (UINT, short, CPoint)
	AfxSig_vws,
};

struct AFX_MSGMAP_ENTRY {
	UINT nMessage;   // windows message
	UINT nCode;      // control code or WM_NOTIFY code
	UINT nID;        // control ID (or 0 for windows messages)
	UINT nLastID;    // used for entries specifying a range of control id's
	UINT nSig;       // signature type (action) or pointer to message #
	void* pfn;       // routine to call (or special value)
};

void __fastcall selection_test(CPortalView* thisptr, void*) {
	const char* selection_table[] = { "??? (base class)", "None", "Roll", "EventGraph", "Key", "Track", "AllTrack", "EventList" };
	char buf[1024];
	snprintf(buf, 1024, "GetType: %s", selection_table[thisptr->m_pSelection->GetType()]);
	MessageBoxA(NULL, buf, "Works", 0);
	Common::Log(Common::LogType::None, "wow");
	Common::Log(Common::LogType::Info, "wow");
	Common::Log(Common::LogType::Warn, "wow");
	//Common::Fatal(NULL, "error message goes here...here's a number %d", 42);
}

AFX_MSGMAP_ENTRY g_custom_portal_entries[] = {
	//{WM_COMMAND, 0xFFFFFFFF, ID_CUSTOMITEM1, ID_CUSTOMITEM1, AfxSig_cmdui, (void*)CPORTALVIEW_ENABLEIFSELECTION},
	{WM_COMMAND, 0, ID_CUSTOMITEM1, ID_CUSTOMITEM1, AfxSig_vv, selection_test},
	{0, 0, 0, 0, 0, nullptr}, // terminator
};

void __fastcall open_refaudio(CPortalView* thisptr, void*) {
	ReferenceAudio::OpenDialog();
}

void __fastcall open_settings(CPortalView* thisptr, void*) {
	Settings::OpenDialog();
}

void __fastcall open_github(CPortalView* thisptr, void*) {
	ShellExecute(NULL, "open", "https://github.com/khang06/dominohook", NULL, NULL, SW_SHOWNORMAL);
}

AFX_MSGMAP_ENTRY g_custom_frame_entries[] = {
	{WM_COMMAND, 0, ID_REFAUDIO, ID_REFAUDIO, AfxSig_vv, open_refaudio},
	{WM_COMMAND, 0, ID_SETTINGS, ID_SETTINGS, AfxSig_vv, open_settings},
	{WM_COMMAND, 0, ID_GITHUB, ID_GITHUB, AfxSig_vv, open_github},
	{0, 0, 0, 0, 0, nullptr}, // terminator
};