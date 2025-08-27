import { contextBridge, ipcRenderer } from 'electron'
import { electronAPI } from '@electron-toolkit/preload'
import { WindowCommandType } from '../shared/WindowCommandType'
import { FolderPath } from '../shared/FolderPath'
import { DirectoryExistResult } from '../shared/BackendPromise'

// Custom APIs for renderer
const api = {
  // API: Window resize
  resizeWindowFunc: (type: WindowCommandType) => ipcRenderer.invoke('resizeWindowAPI', type),

  // API: Open folder
  openFolderFunc: (): Promise<FolderPath> => ipcRenderer.invoke('openFolderAPI'),

  // API: Check if directory exists
  checkIfDirectoryExistsFunc: (path: string, create_mode: boolean): Promise<DirectoryExistResult> =>
    ipcRenderer.invoke('checkIfDirectoryExistsAPI', path, create_mode),

  // API: Create workspace
  createWorkspaceFunc: (path: string, name: string): Promise<DirectoryExistResult> =>
    ipcRenderer.invoke('createWorkspaceAPI', path, name)
}

// Use `contextBridge` APIs to expose Electron APIs to
// renderer only if context isolation is enabled, otherwise
// just add to the DOM global.
if (process.contextIsolated) {
  try {
    contextBridge.exposeInMainWorld('electron', electronAPI)
    contextBridge.exposeInMainWorld('api', api)
  } catch (error) {
    console.error(error)
  }
} else {
  // @ts-ignore (define in dts)
  window.electron = electronAPI
  // @ts-ignore (define in dts)
  window.api = api
}
