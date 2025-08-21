import { JSX } from "react"
import { Typography } from "antd"
import { FolderOpenOutlined, FolderAddOutlined } from "@ant-design/icons"

export default function ErrNoWorkspaceOpened():JSX.Element {
  return (
    <>
      <div className="no-workspace-opened-container no-select">
        <Typography.Title level={2} className="no-select">No Workspace Opened</Typography.Title>
        <Typography.Text className="app-text no-select">To open a workspace, you may visit the menu bar's "File" section or simply select one option from below:</Typography.Text>
        <Typography>
          <ul>
            <li className="no-select">
              <Typography.Link className="app-text no-select">
                <FolderOpenOutlined />
                &nbsp;&nbsp;
                Open workspace
              </Typography.Link>
            </li>

            <li className="no-select">
              <Typography.Link className="app-text no-select">
                <FolderAddOutlined />
                &nbsp;&nbsp;
                Create workspace
              </Typography.Link>
            </li>
          </ul>
        </Typography>
      </div>
    </>
  )
}
