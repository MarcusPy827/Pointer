import { JSX } from 'react'
import { useTranslation } from 'react-i18next'
import { useWorkspaceContext } from '../context/WorkspaceBridge'
import type { WorkspaceInfoQueryPayload } from '../../../shared/BackendPromise'

export default function ToolBar(): JSX.Element {
  const { t } = useTranslation()
  const { workspacePath, workspaceState } = useWorkspaceContext()

  const getWorkspaceName = (query: WorkspaceInfoQueryPayload): string => {
    if (!query.query_state) {
      return 'Pointer'
    }

    if (query.name === '') {
      return t('unnamed_workspace')
    }

    return query.name
  }

  return (
    <>
      <div className="tool-bar">
        <span className="tool-bar-title no-select" draggable={false}>
          {getWorkspaceName(workspaceState)}
        </span>

        <span className="tool-bar-subtitle no-select" draggable={false}>
          {workspacePath || t('no_workspace_opened_title')}
        </span>
      </div>
    </>
  )
}
