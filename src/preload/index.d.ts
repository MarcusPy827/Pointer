import { ElectronAPI } from '@electron-toolkit/preload'
import { WindowCommandType } from '../shared/WindowCommandType'
import { FolderPath } from '../shared/FolderPath'
import { DirectoryExistResult } from '../shared/BackendPromise'

interface RenderAPI {
  resizeWindowFunc: (type: WindowCommandType) => Promise<void>
  openFolderFunc: () => Promise<FolderPath>
  checkIfDirectoryExistsFunc: (path: string, create_mode: boolean) => Promise<DirectoryExistResult>
  createWorkspaceFunc: (path: string, name: string) => Promise<DirectoryExistResult>
  openWorkspaceFunc: (path: string) => Promise<DirectoryExistResult>
}

declare global {
  interface Window {
    electron: ElectronAPI
    api: unknown
  }
}
