import { ChangeEvent, JSX, useState } from 'react'
import { Typography, Modal, Input, Space, Button, message } from 'antd'
import {
  FolderOpenOutlined,
  FolderAddOutlined,
  EditOutlined,
  FolderOutlined
} from '@ant-design/icons'
import { useTranslation } from 'react-i18next'
import { FolderPath } from '../../../shared/FolderPath'
import { WorkspaceInfoQueryPayload } from '../../../shared/BackendPromise'

export default function ErrNoWorkspaceOpened(): JSX.Element {
  const { t } = useTranslation()

  const [messageApi, contextHolder] = message.useMessage()
  const [isWorkspaceCreationDialogOpened, setIsWorkspaceCreationDialogOpened] = useState(false)
  const [workspaceCreationDialogLoading, setWorkspaceCreationDialogLoading] = useState(false)
  const [workspaceName, setWorkspaceName] = useState<string>('')
  const [workspacePath, setWorkspacePath] = useState<string>('')

  const handleOpenWorkspace = async (path?: string): Promise<void> => {
    let folderPath = path
    if (!path) {
      const result: folderPath = await window.api.openFolderFunc()
      if (result.cancelled) {
        messageApi.open({
          type: 'warning',
          content: t('cancelled_message')
        })
      } else {
        if (result.path != undefined) {
          folderPath = result.path
        } else {
          messageApi.open({
            type: 'warning',
            content: t('err_invalid_path')
          })
        }
      }
    }

    const queryResult: WorkspaceInfoQueryPayload = await window.api.openWorkspaceFunc(folderPath)
    console.info(`Trying to open ${folderPath}.`)
    if (queryResult.query_state) {
      messageApi.open({
        type: 'success',
        content: t('ok_workspace_opened')
      })

      let workspaceInfoLog: string = 'Workspace opened.\n'
      workspaceInfoLog += `${JSON.stringify(queryResult)}`
      console.info(workspaceInfoLog)
    } else {
      console.error(
        `An error occurred while opening the workspace.\nThe backend returned: ${queryResult.err_msg}.`
      )
    }
  }

  const showWorkspaceCreationDialog = (): void => {
    setIsWorkspaceCreationDialogOpened(true)
  }

  const execWorkspaceCreation = async (): Promise<void> => {
    if (workspaceName === '') {
      setWorkspaceCreationDialogLoading(false)
      messageApi.open({
        type: 'error',
        content: t('err_empty_workspace_name')
      })
      return
    } else if (workspacePath === '') {
      setWorkspaceCreationDialogLoading(false)
      messageApi.open({
        type: 'error',
        content: t('err_empty_workspace_path')
      })
      return
    }

    const isFolderExist = await window.api.createWorkspaceFunc(workspacePath, workspaceName)
    if (!isFolderExist.result) {
      setWorkspaceCreationDialogLoading(false)
      messageApi.open({
        type: 'error',
        content: t('err_log_in_console')
      })

      console.error(isFolderExist.result_msg)
      return
    } else {
      setWorkspaceCreationDialogLoading(false)
      setIsWorkspaceCreationDialogOpened(false)
      messageApi.open({
        type: 'success',
        content: t('ok_workspace_created')
      })

      handleOpenWorkspace(workspacePath)
    }
  }

  const handleWorkspaceCreation = (): void => {
    setWorkspaceCreationDialogLoading(true)
    execWorkspaceCreation()
  }

  const handleWorkspaceCreationCancel = (): void => {
    setIsWorkspaceCreationDialogOpened(false)
  }

  const handleWorkspaceBrowse = async (): Promise<void> => {
    const result: FolderPath = await window.api.openFolderFunc()
    if (result.cancelled) {
      messageApi.open({
        type: 'warning',
        content: t('cancelled_message')
      })
    } else {
      if (result.path != undefined) {
        setWorkspacePath(result.path)
      }
    }
  }

  return (
    <>
      {contextHolder}
      <Modal
        title={t('create_workspace_title')}
        open={isWorkspaceCreationDialogOpened}
        confirmLoading={workspaceCreationDialogLoading}
        onOk={() => handleWorkspaceCreation()}
        onCancel={() => handleWorkspaceCreationCancel()}
        okText={t('ok_text')}
        cancelText={t('cancel_text')}
      >
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_name_label_desc')}
        </Typography.Text>
        <br className="no-select" draggable={false} />
        <Input
          className="no-select"
          prefix={<EditOutlined />}
          draggable={false}
          onChange={(event: ChangeEvent<HTMLInputElement>) => setWorkspaceName(event.target.value)}
        />

        <br className="no-select" draggable={false} />
        <br className="no-select" draggable={false} />
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_path_label_desc')}
        </Typography.Text>
        <br className="no-select" draggable={false} />
        <Space.Compact style={{ width: '100%' }}>
          <Input
            className="no-select"
            prefix={<FolderOutlined />}
            draggable={false}
            value={workspacePath}
            onChange={(event: ChangeEvent<HTMLInputElement>) =>
              setWorkspacePath(event.target.value)
            }
          />
          <Button type="primary" onClick={() => handleWorkspaceBrowse()}>
            {t('browse_action')}
          </Button>
        </Space.Compact>

        <br className="no-select" draggable={false} />
        <br className="no-select" draggable={false} />
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_icon_settings_desc')}
        </Typography.Text>

        <br className="no-select" draggable={false} />
      </Modal>

      <div className="no-workspace-opened-container no-select">
        <Typography.Title level={2} className="no-select">
          {t('no_workspace_opened_title')}
        </Typography.Title>

        <Typography.Text className="app-text no-select">{t('open_workspace_desc')}</Typography.Text>

        <Typography>
          <ul>
            <li className="no-select">
              <Typography.Link className="app-text no-select" onClick={() => handleOpenWorkspace()}>
                <FolderOpenOutlined />
                &nbsp;&nbsp;
                {t('open_workspace_action')}
              </Typography.Link>
            </li>

            <li className="no-select">
              <Typography.Link
                className="app-text no-select"
                onClick={() => showWorkspaceCreationDialog()}
              >
                <FolderAddOutlined />
                &nbsp;&nbsp;
                {t('create_workspace_action')}
              </Typography.Link>
            </li>
          </ul>
        </Typography>
      </div>
    </>
  )
}
