import { createContext, useContext } from 'react'
import { WorkspaceInfoQueryPayload } from '../../../shared/BackendPromise'

export interface WorkspaceContextBridge {
  isWorkspaceOpened: boolean
  setIsWorkspaceOpened: (val: boolean) => void
  workspacePath: string
  setWorkspacePath: (val: string) => void
  workspaceState: WorkspaceInfoQueryPayload
  setWorkspaceState: (val: WorkspaceInfoQueryPayload) => void
}

export const WorkspaceContext = createContext<WorkspaceContextBridge | null>(null)

export function useWorkspaceContext(): WorkspaceContextBridge {
  const cur_context = useContext(WorkspaceContext)
  if (!cur_context) {
    throw new Error('🔑 Workspace status is visited outside the context, please fix this error...')
  }
  return cur_context
}
